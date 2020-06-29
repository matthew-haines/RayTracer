#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "surface.hpp"
#include "vector3.hpp"
#include "ray.hpp"

class Primitive {
    public:
        Surface* surface;
        virtual double intersect(Ray ray, Vector3 *intersectPoint, Vector3 *normal)=0;
};

#endif