#ifndef BVH_INTERSECTOR_HPP
#define BVH_INTERSECTOR_HPP
#include "intersector.hpp"
#include "bound.hpp"
#include <vector>

struct BVHNode;

class BVHIntersector: public Intersector {
    // Builds with surface area heuristic
    private:
        BVHNode* root; 
        std::vector<Bound> bounds;
    public:
        BVHIntersector(Scene* scene);
        bool getIntersect(Ray ray, Intersection& intersection);
        void buildNode(BVHNode* precursor);
};  

#endif
