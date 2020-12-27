#ifndef BVH_INTERSECTOR_HPP
#define BVH_INTERSECTOR_HPP

#include "intersector.hpp"
#include "bound.hpp"
#include "thread_safe_queue.hpp"
#include <functional>
#include <atomic>
#include <memory>
#include <vector>

struct BVHNode;

// Bounding Volume Hierarchy Intersector. Uses Surface Area Heuristic to construct. 
class BVHIntersector: public Intersector {
    private:
        std::shared_ptr<BVHNode> root; 
        std::vector<Bound> bounds;
        int processed = 0;
        int added = 0;
        // Worker function used during construction of the BVH, one instance per thread.
        void workerFunction(ThreadSafeQueue<std::shared_ptr<BVHNode> >& queue, std::atomic<int>* complete, const int total);
    public:
        BVHIntersector(Scene* const scene, const int threads);
        bool getIntersect(const Ray ray, Intersection& intersection) const;
        // Recursive, single threaded BVH construction function, not actually used.
        void buildNodeRecursive(std::shared_ptr<BVHNode> const precursor);
        // Constructs a single node in the BVH, used by workerFunction.
        void buildNode(BVHNode& precursor, std::shared_ptr<BVHNode>* const left, std::shared_ptr<BVHNode>* const right);
        void parallelConstruct(const int threads);
};  

#endif
