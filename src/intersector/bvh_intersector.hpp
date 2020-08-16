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
        int processed = 0;
        int added = 0;
        void WorkerFunction(ThreadSafeQueue<BVHNode*>& queue, int& complete, int total);
    public:
        int intersections = 0;
        int calls = 0;
        BVHIntersector(Scene* scene);
        bool getIntersect(Ray ray, Intersection& intersection);
        void buildNodeRecursive(BVHNode* precursor);
        void buildNode(BVHNode* precursor, BVHNode** left, BVHNode** right);
        void ParallelConstruct(int threads);
};  

#endif
