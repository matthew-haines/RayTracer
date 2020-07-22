#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP
#include "../intersection.hpp"
#include "../primitive/primitive.hpp"
#include "../ray.hpp"
#include <vector>

class Intersector {
    public:
        virtual bool getIntersect(Ray ray, Intersection& intersection)=0;
        virtual bool getShadowIntersect(Ray ray, double maxDistance)=0;
};

#endif
