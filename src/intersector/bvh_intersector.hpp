#ifndef BVH_INTERSECTOR_HPP
#define BVH_INTERSECTOR_HPP
#include "intersector.hpp"

class BVHIntersector: public Intersector {
    public:
        BVHIntersector(Scene* scene);
        bool getIntersect(Ray ray, Intersection& intersection);
};  

#endif
