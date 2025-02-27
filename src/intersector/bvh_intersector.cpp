#include "bvh_intersector.hpp"
#include "thread_safe_queue.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include <tuple>
#include <type_traits>

struct BVHNode {
    Bound bound;
    std::shared_ptr<BVHNode> child1=nullptr;
    std::shared_ptr<BVHNode> child2=nullptr;
    std::vector<int> primitives;
    int dim;
};

BVHIntersector::BVHIntersector(Scene* const scene, const int threads): Intersector(scene) {
    bounds = std::vector<Bound>(scene->primitives.size());
    root = std::make_shared<BVHNode>();
    root->primitives = std::vector<int>(bounds.size());
    Vector3 min(std::numeric_limits<double>::max());
    Vector3 max(std::numeric_limits<double>::lowest());
    for (int i = 0; i < scene->primitives.size(); i++) {
        bounds[i] = scene->primitives[i]->getBound(); // need to implement
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
    parallelConstruct(threads);
}

bool BVHIntersector::getIntersect(const Ray ray, Intersection& intersection) const {
    // Because of the strict performance requirements, I adapted this from PBRT
    Vector3 invDir = 1. / ray.direction;
    int dirIsNeg[3] = {ray.direction.x < 0., ray.direction.y < 0., ray.direction.z < 0.};

    std::shared_ptr<BVHNode> nodeStack[64];
    int stackIndex = 0;
    nodeStack[0] = root;
    Vector3 normal;
    Vector3 intersect;
    
    bool intersected = false;
    double minDist = std::numeric_limits<double>::max();

    while (stackIndex > -1) {
        std::shared_ptr<BVHNode> node = nodeStack[stackIndex];
        if (node->bound.rayIntersect(ray, invDir, dirIsNeg)) {
            if (node->child1 == nullptr) {
                for (int primIndex : node->primitives) {
                    double distance = scene->primitives[primIndex]->intersect(ray, &intersect, &normal);
                    if (distance != -1 && distance < minDist) {
                        intersected = true;
                        minDist = distance;
                        intersection.distance = distance;
                        intersection.intersect = intersect;
                        intersection.normal = normal;
                        intersection.primitive = scene->primitives[primIndex];
                    }
                }
                stackIndex--;
            } else {
                if (dirIsNeg[node->dim]) {
                    nodeStack[stackIndex] = node->child1;
                    nodeStack[++stackIndex] = node->child2;
                } else {
                    nodeStack[stackIndex] = node->child2;
                    nodeStack[++stackIndex] = node->child1;
                }
            }
        } else {
            stackIndex--;
        }
    }

    return intersected;
}

void BVHIntersector::buildNodeRecursive(std::shared_ptr<BVHNode> const precursor) {
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

    Bound centroidBound;
    for (int index : precursor->primitives) {
        centroidBound = Bound::computeUnion(centroidBound, bounds[index].centroid);
    }
    int dim = 0;
    double maxRange = std::numeric_limits<double>::lowest();
    for (int i = 0; i < 3; i++) {
        double range = centroidBound.max[i] - centroidBound.min[i];
        if (range > maxRange) {
            maxRange = range;
            dim = i;
        }
    }

    precursor->dim = dim;

    for (int index : precursor->primitives) {
        int bucket = (int)((double)bucketCount * (bounds[index].centroid[dim] - precursor->bound.min[dim]) / maxRange);
        buckets[bucket].primitives.push_back(index);
        buckets[bucket].bound = Bound::computeUnion(bounds[index], buckets[bucket].bound);
    }

    struct PartitionCandidate {
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
        candidates[i].leftBound = Bound::computeUnion(buckets[i].bound, candidates[i-1].leftBound);
        candidates[i].leftCount = buckets[i].primitives.size() + candidates[i-1].leftCount;
        
        candidates[bucketCount-i-2].rightBound = Bound::computeUnion(buckets[bucketCount-i-1].bound, candidates[bucketCount-i-1].rightBound);
        candidates[bucketCount-i-2].rightCount = buckets[bucketCount-i-1].primitives.size() + candidates[bucketCount-i-1].rightCount;
    }

    int bestPartition = 0;
    double bestCost = std::numeric_limits<double>::max(); 
    for (int i = 0; i < bucketCount-1; i++) {
        double cost = 0.125 + (candidates[i].leftCount * candidates[i].leftBound.surfaceArea() + candidates[i].rightCount * candidates[i].rightBound.surfaceArea()) / precursor->bound.surfaceArea();
        if (cost < bestCost) {
            bestCost = cost;
            bestPartition = i;
        }
    }

    if (bestCost < precursor->primitives.size()) {
        auto left = std::make_shared<BVHNode>();
        auto right = std::make_shared<BVHNode>();
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

void BVHIntersector::buildNode(BVHNode& precursor, std::shared_ptr<BVHNode>* const left, std::shared_ptr<BVHNode>* const right) {
    if (precursor.primitives.size() == 1) {
        return;
    }

    struct Bucket {
        std::vector<int> primitives;
        Bound bound;
        Bucket(): primitives(std::vector<int>()), bound(Bound()) {};
    };

    const int bucketCount = 12; // magic number
    Bucket buckets[bucketCount];
    
    Bound centroidBound;
    for (int index : precursor.primitives) {
        centroidBound = Bound::computeUnion(centroidBound, bounds[index].centroid);
    }
    int dim = 0;
    double maxCentroidRange = std::numeric_limits<double>::lowest();
    for (int i = 0; i < 3; i++) {
        double range = centroidBound.max[i] - centroidBound.min[i];
        if (range > maxCentroidRange) {
            maxCentroidRange = range;
            dim = i;
        }
    }
    double maxRange = precursor.bound.max[dim] - precursor.bound.min[dim];
    if (maxRange == 0) {
        return;
    }
    precursor.dim = dim;

    for (int index : precursor.primitives) {
        int bucket = (int)((double)bucketCount * (bounds[index].centroid[dim] - precursor.bound.min[dim]) / maxRange);
        bucket = bucket == bucketCount ? bucket - 1 : bucket;
        buckets[bucket].primitives.push_back(index);
        buckets[bucket].bound = Bound::computeUnion(bounds[index], buckets[bucket].bound);
    }

    struct PartitionCandidate {
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
        candidates[i].leftBound = Bound::computeUnion(buckets[i].bound, candidates[i-1].leftBound);
        candidates[i].leftCount = buckets[i].primitives.size() + candidates[i-1].leftCount;
        
        candidates[bucketCount-i-2].rightBound = Bound::computeUnion(buckets[bucketCount-i-1].bound, candidates[bucketCount-i-1].rightBound);
        candidates[bucketCount-i-2].rightCount = buckets[bucketCount-i-1].primitives.size() + candidates[bucketCount-i-1].rightCount;
    }

    int bestPartition = 0;
    double bestCost = std::numeric_limits<double>::max(); 
    for (int i = 0; i < bucketCount-1; i++) {
        double cost = 0.125 + (candidates[i].leftCount * candidates[i].leftBound.surfaceArea() + candidates[i].rightCount * candidates[i].rightBound.surfaceArea()) / precursor.bound.surfaceArea();
        if (cost < bestCost) {
            bestCost = cost;
            bestPartition = i;
        }
    }

    if (bestCost < precursor.primitives.size()) {
        *left = std::make_shared<BVHNode>(); 
        *right = std::make_shared<BVHNode>(); 
        (**left).bound = candidates[bestPartition].leftBound;
        for (int i = 0; i <= bestPartition; i++) {
            (**left).primitives.insert((**left).primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        (**right).bound = candidates[bestPartition].rightBound;
        for (int i = bestPartition+1; i < bucketCount; i++) {
            (**right).primitives.insert((**right).primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        precursor.child1 = *left;
        precursor.child2 = *right;
    }
    return;
}

void BVHIntersector::workerFunction(ThreadSafeQueue<std::shared_ptr<BVHNode> >& queue, std::atomic<int>* complete, const int total) {
    while (*complete < total) {
        auto node = queue.pop();
        if (node == nullptr) {
            queue.push(nullptr);
            break;
        }
        std::shared_ptr<BVHNode> left(nullptr);
        std::shared_ptr<BVHNode> right(nullptr);
        buildNode(*node, &left, &right);
        if (left != nullptr) { // not leaf
            added++;
            queue.push(left);
            queue.push(right);
        } else {
            *complete += node->primitives.size();
            processed++;
            if (*complete == total) {
                queue.push(nullptr);
            }
        }
    }
}

void BVHIntersector::parallelConstruct(const int threads) {
    ThreadSafeQueue<std::shared_ptr<BVHNode> > queue;
    queue.push(root);
    std::vector<std::thread> threadpool;
    std::atomic<int> complete = 0;
    int total = scene->primitives.size();
    for (int i = 0; i < threads; i++) {
        auto func = std::bind(&BVHIntersector::workerFunction, this, std::ref(queue), &complete, total);
        threadpool.emplace_back(func);
    }

    for (auto& thread : threadpool) {
        thread.join();
    }
}