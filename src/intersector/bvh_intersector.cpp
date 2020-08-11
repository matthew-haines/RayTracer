#include "bvh_intersector.hpp"

struct BVHNode {
    Bound bound;
    BVHNode* child1=nullptr;
    BVHNode* child2=nullptr;
    std::vector<int> primitives;
};

BVHIntersector::BVHIntersector(Scene* scene): Intersector(scene) {
    bounds = std::vector<Bound>(scene->primitives.size());
    root = new BVHNode;
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
    buildNode(root);
}

bool BVHIntersector::getIntersect(Ray ray, Intersection& intersection) {
    return (bool)root->child1;
}

void BVHIntersector::buildNode(BVHNode* precursor) {
    if (precursor->primitives.size() == 1) {
        return;
    }

    struct Bucket {
        std::vector<int> primitives;
        Bound bound;
        Bucket(): primitives(std::vector<int>()), bound(Bound()) {};
    };

    const int bucketCount = 10; // yay magic number
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
    
    PartitionCandidate candidates[bucketCount];
    // theres an edge case here
    candidates[0].leftBound = buckets[0].bound;
    candidates[0].leftCount = buckets[0].primitives.size();
    candidates[bucketCount-1].rightBound = buckets[bucketCount-1].bound;
    candidates[bucketCount-1].rightCount = buckets[bucketCount-1].primitives.size();
    for (int i = 1; i < bucketCount; i++) {
        if (buckets[i].primitives.size() != 0) {
            if (candidates[i-1].leftCount != 0) {
                candidates[i].leftBound = Bound::Union(buckets[i].bound, candidates[i-1].leftBound);
            } else {
                candidates[i].leftBound = buckets[i].bound;
            }
        } else {
            candidates[i].leftBound = candidates[i-1].leftBound;
        }
        candidates[i].leftCount = buckets[i].primitives.size() + candidates[i-1].leftCount;
        
        if (buckets[bucketCount-i-1].primitives.size() != 0) {
            if (candidates[bucketCount-i].rightCount != 0) {
                candidates[bucketCount-i-1].rightBound = Bound::Union(buckets[bucketCount-i-1].bound, candidates[bucketCount-i].rightBound);
            } else {
                candidates[bucketCount-i-1].rightBound = buckets[bucketCount-i].bound;
            }
        } else {
            candidates[bucketCount-i-1].rightBound = candidates[bucketCount-i].rightBound;
        }
        candidates[bucketCount-i-1].rightCount = buckets[bucketCount-i-1].primitives.size() + candidates[bucketCount-i].rightCount;
    }

    int bestPartition = 0;
    double bestCost = std::numeric_limits<double>::max(); 
    for (int i = 0; i < bucketCount; i++) {
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
        for (int i = 0; i < bestPartition; i++) {
            left->primitives.insert(left->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        right->bound = candidates[bestPartition].rightBound;
        for (int i = bestPartition; i < bucketCount; i++) {
            right->primitives.insert(right->primitives.end(), buckets[i].primitives.begin(), buckets[i].primitives.end());
        }
        buildNode(left);
        buildNode(right);
        precursor->child1 = left;
        precursor->child2 = right;
    }
    return;
}