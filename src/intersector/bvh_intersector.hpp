#ifndef BVH_INTERSECTOR_HPP
#define BVH_INTERSECTOR_HPP

#include "intersector.hpp"
#include "bound.hpp"
#include "thread_safe_queue.hpp"
#include <functional>
#include <atomic>
#include <vector>

struct BVHNode;

class BVHIntersector: public Intersector {
    // Builds with surface area heuristic
    private:
        BVHNode* root; 
        std::vector<Bound> bounds;
        int processed = 0;
        int added = 0;
        void workerFunction(ThreadSafeQueue<BVHNode*>& queue, std::atomic<int>* complete, int total);
    public:
        BVHIntersector(Scene* scene, int threads);
        bool getIntersect(Ray ray, Intersection& intersection);
        void buildNodeRecursive(BVHNode* precursor);
        void buildNode(BVHNode& precursor, BVHNode** left, BVHNode** right);
        void parallelConstruct(int threads);
};  

#endif
