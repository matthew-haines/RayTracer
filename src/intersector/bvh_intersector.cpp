#include "bvh_intersector.hpp"
#include "thread_safe_queue.hpp"
#include <functional>
#include <thread>

struct BVHNode {
    Bound bound;
    BVHNode* child1=nullptr;
    BVHNode* child2=nullptr;
    std::vector<int> primitives;
    int dim;
};

BVHIntersector::BVHIntersector(Scene* scene): Intersector(scene) {
    bounds = std::vector<Bound>(scene->primitives.size());
    root = new BVHNode();
    root->primitives = std::vector<int>(bounds.size());
    Vector3 min(std::numeric_limits<double>::max());
    Vector3 max(std::numeric_limits<double>::lowest());
    for (int i = 0; i < scene->primitives.size(); i++) {
        bounds[i] = scene->primitives[i]->GetBound(); // need to implement
        root->primitives[i] = i;
        for (int j = 0; j < 3; j++) {
            if (bounds[i].min[j] < min[j]) {
                min[j] = bounds[i].min[j];
            }
            if (bounds[i].max[j] > max[j]) {
                max[j] = bounds[i].max[j];
            }
        }
    }
    root->bound = Bound(min, max);
    //buildNode(root);
    ParallelConstruct(8);
}

bool BVHIntersector::getIntersect(Ray ray, Intersection& intersection) {
    // Because of the strict performance requirements, I adapted this from PBRT
    Vector3 invDir = 1. / ray.direction;
    int dirIsNeg[3] = {ray.direction.x < 0., ray.direction.y < 0., ray.direction.z < 0.};

    BVHNode* nodeStack[64];
    int stackIndex = 0;
    nodeStack[0] = root;

    Vector3 normal;
    Vector3 intersect;
    
    bool intersected = false;
    
    while (true) {
        BVHNode* node = nodeStack[stackIndex];
        if (node->bound.RayIntersect(ray, invDir, dirIsNeg)) {
            if (node->child1 == nullptr) {
                double minDist = std::numeric_limits<double>::max();
                for (int primIndex : node->primitives) {
                    double distance = scene->primitives[primIndex]->Intersect(ray, &intersect, &normal);
                    if (distance != -1 && distance < minDist) {
                        intersected = true;
                        minDist = distance;
                        intersection.distance = distance;
                        intersection.intersect = intersect;
                        intersection.normal = normal;
                    }
                }
                if (intersected) {
                    return true;
                }
            } else {
                if (dirIsNeg[node->dim]) {
                    nodeStack[++stackIndex] = node->child1;
                    nodeStack[++stackIndex] = node->child2;
                } else {
                    nodeStack[++stackIndex] = node->child2;
                    nodeStack[++stackIndex] = node->child1;
                }
            }
        }
        stackIndex--;
    }

    return false;
}

void BVHIntersector::buildNodeRecursive(BVHNode* precursor) {
    if (precursor->primitives.size() == 1) {
        return;
    }

    struct Bucket {
        std::vector<int> primitives;
        Bound bound;
        Bucket(): primitives(std::vector<int>()), bound(Bound()) {};
    };

    const int bucketCount = 12; // yay magic number
    Bucket buckets[bucketCount];

    int dim;
    double maxRange = 0.0;
    for (int i = 0; i < 3; i++) {
        double range = precursor->bound.max[i] - precursor->bound.min[i];
        if (range > maxRange) {
            dim = i;
            maxRange = range;
        }
    }

    precursor->dim = dim;

    for (int index : precursor->primitives) {
        int bucket = (int)((double)bucketCount * (bounds[index].centroid[dim] - precursor->bound.min[dim]) / maxRange);
        buckets[bucket].primitives.push_back(index);
        buckets[bucket].bound = Bound::Union(bounds[index], buckets[bucket].bound);
    }

    struct PartitionCandidate {
        int cost=0;
        Bound leftBound;
        Bound rightBound;
        int leftCount=0;
        int rightCount=0; 
    };
    
    PartitionCandidate candidates[bucketCount-1];
    candidates[0].leftBound = buckets[0].bound;
    candidates[0].leftCount = buckets[0].primitives.size();
    candidates[bucketCount-2].rightBound = buckets[bucketCount-1].bound;
    candidates[bucketCount-2].rightCount = buckets[bucketCount-1].primitives.size();
    for (int i = 1; i < bucketCount-1; i++) {
        candidates[i].leftBound = Bound::Union(buckets[i].bound, candidates[i-1].leftBound);
        candidates[i].leftCount = buckets[i].primitives.size() + candidates[i-1].leftCount;
        
        candidates[bucketCount-i-2].rightBound = Bound::Union(buckets[bucketCount-i-1].bound, candidates[bucketCount-i-1].rightBound);
        candidates[bucketCount-i-2].rightCount = buckets[bucketCount-i-1].primitives.size() + candidates[bucketCount-i-1].rightCount;
    }

    int bestPartition = 0;
    double bestCost = std::numeric_limits<double>::max(); 
    for (int i = 0; i < bucketCount-1; i++) {
        double cost = 0.125 + (candidates[i].leftCount * candidates[i].leftBound.SurfaceArea() + candidates[i].rightCount * candidates[i].rightBound.SurfaceArea()) / precursor->bound.SurfaceArea();
        if (cost < bestCost) {
            bestCost = cost;
            bestPartition = i;
        }
    }

    if (bestCost < precursor->primitives.size()) {
        BVHNode* left = new BVHNode();
        BVHNode* right = new BVHNode();
        left->bound = candidates[bestPartition].leftBound;
        for (int i = 0; i <= bestPartition; i++) {
            left->primitives.insert(left->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        right->bound = candidates[bestPartition].rightBound;
        for (int i = bestPartition+1; i < bucketCount; i++) {
            right->primitives.insert(right->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        buildNodeRecursive(left);
        buildNodeRecursive(right);
        precursor->child1 = left;
        precursor->child2 = right;
    }
    return;
}

void BVHIntersector::buildNode(BVHNode* precursor, BVHNode* left, BVHNode* right) {
    if (precursor->primitives.size() == 1) {
        return;
    }

    struct Bucket {
        std::vector<int> primitives;
        Bound bound;
        Bucket(): primitives(std::vector<int>()), bound(Bound()) {};
    };

    const int bucketCount = 12; // yay magic number
    Bucket buckets[bucketCount];

    int dim;
    double maxRange = 0.0;
    for (int i = 0; i < 3; i++) {
        double range = precursor->bound.max[i] - precursor->bound.min[i];
        if (range > maxRange) {
            dim = i;
            maxRange = range;
        }
    }

    precursor->dim = dim;

    for (int index : precursor->primitives) {
        int bucket = (int)((double)bucketCount * (bounds[index].centroid[dim] - precursor->bound.min[dim]) / maxRange);
        buckets[bucket].primitives.push_back(index);
        buckets[bucket].bound = Bound::Union(bounds[index], buckets[bucket].bound);
    }

    struct PartitionCandidate {
        int cost=0;
        Bound leftBound;
        Bound rightBound;
        int leftCount=0;
        int rightCount=0; 
    };
    
    PartitionCandidate candidates[bucketCount-1];
    candidates[0].leftBound = buckets[0].bound;
    candidates[0].leftCount = buckets[0].primitives.size();
    candidates[bucketCount-2].rightBound = buckets[bucketCount-1].bound;
    candidates[bucketCount-2].rightCount = buckets[bucketCount-1].primitives.size();
    for (int i = 1; i < bucketCount-1; i++) {
        candidates[i].leftBound = Bound::Union(buckets[i].bound, candidates[i-1].leftBound);
        candidates[i].leftCount = buckets[i].primitives.size() + candidates[i-1].leftCount;
        
        candidates[bucketCount-i-2].rightBound = Bound::Union(buckets[bucketCount-i-1].bound, candidates[bucketCount-i-1].rightBound);
        candidates[bucketCount-i-2].rightCount = buckets[bucketCount-i-1].primitives.size() + candidates[bucketCount-i-1].rightCount;
    }

    int bestPartition = 0;
    double bestCost = std::numeric_limits<double>::max(); 
    for (int i = 0; i < bucketCount-1; i++) {
        double cost = 0.125 + (candidates[i].leftCount * candidates[i].leftBound.SurfaceArea() + candidates[i].rightCount * candidates[i].rightBound.SurfaceArea()) / precursor->bound.SurfaceArea();
        if (cost < bestCost) {
            bestCost = cost;
            bestPartition = i;
        }
    }

    if (bestCost < precursor->primitives.size()) {
        left = new BVHNode();
        right = new BVHNode();
        left->bound = candidates[bestPartition].leftBound;
        for (int i = 0; i <= bestPartition; i++) {
            left->primitives.insert(left->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        right->bound = candidates[bestPartition].rightBound;
        for (int i = bestPartition+1; i < bucketCount; i++) {
            right->primitives.insert(right->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        precursor->child1 = left;
        precursor->child2 = right;
    }
    return;
}

void BVHIntersector::WorkerFunction(ThreadSafeQueue<std::function<void(BVHNode*, BVHNode*)>>& queue, int& complete) {
    while (complete < scene->primitives.size()) {
        std::function<void(BVHNode*, BVHNode*)> job = queue.pop();
        BVHNode* left;
        BVHNode* right;
        job(left, right);
        if (left != nullptr) {
            auto leftFunc = std::bind(&BVHIntersector::buildNode, this, left, std::placeholders::_1, std::placeholders::_2);
            auto rightFunc = std::bind(&BVHIntersector::buildNode, this, right, std::placeholders::_1, std::placeholders::_2);
            queue.push(leftFunc);
            queue.push(rightFunc);
        } else {
            complete++;
        }
    }
}

void BVHIntersector::ParallelConstruct(int threads) {
    ThreadSafeQueue<std::function<void(BVHNode*, BVHNode*)>> queue;
    queue.push(std::bind(&BVHIntersector::buildNode, this, root, std::placeholders::_1, std::placeholders::_2));
    std::vector<std::thread> threadpool;
    int complete = 0;
    for (int i = 0; i < threads; i++) {
        auto func = std::bind(&BVHIntersector::WorkerFunction, this, queue, complete);
        threadpool.emplace_back(func);
    }

    for (auto& thread : threadpool) {
        thread.join();
    }
}