#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "material.hpp"
#include "vector3.hpp"
#include "ray.hpp"

class Primitive {
    public:
        Material* material;
        virtual double intersect(Ray ray, Vector3 *intersect, Vector3 *normal)=0; // Must return -1 if no intersect
};

#endif