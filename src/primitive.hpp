#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "surface.hpp"
#include "vector3.hpp"
#include "ray.hpp"

class Primitive {
    public:
        Surface* surface;
        virtual Vector3 intersect(Ray ray);
        virtual Vector3 normal(Vector3 point);
};

#endif