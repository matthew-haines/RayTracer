#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "primitive.hpp"
#include "vector3.hpp"

class Sphere: Primitive {
    private:
        Vector3 center;
        double radius;
    public:
        Sphere(Vector3 center, double radius);
        Vector3 intersect(Ray ray);
        Vector3 normal();
};

#endif