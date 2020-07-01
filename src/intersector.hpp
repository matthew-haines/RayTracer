#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP
#include "primitive.hpp"
#include "ray.hpp"
#include <vector>

class Intersector {
    public:
        virtual double getIntersect(Ray ray, Vector3 *intersect, Vector3 *normal, Primitive **primitive)=0;
        virtual bool getShadowIntersect(Ray ray, double maxDistance)=0;
};

#endif
