#ifndef BVH_INTERSECTOR_HPP
#define BVH_INTERSECTOR_HPP
#include "intersector.hpp"
#include "bound.hpp"
#include "thread_safe_queue.hpp"
#include <functional>
#include <vector>

struct BVHNode;

class BVHIntersector: public Intersector {
    // Builds with surface area heuristic
    private:
        BVHNode* root; 
        std::vector<Bound> bounds;
        void WorkerFunction(ThreadSafeQueue<std::function<void(BVHNode*, BVHNode*)>>& queue, int& complete);
    public:
        BVHIntersector(Scene* scene);
        bool getIntersect(Ray ray, Intersection& intersection);
        void buildNodeRecursive(BVHNode* precursor);
        void buildNode(BVHNode* precursor, BVHNode* left, BVHNode* right);
        void ParallelConstruct(int threads);
};  

#endif
