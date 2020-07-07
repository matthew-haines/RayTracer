#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "primitive.hpp"

class Sphere: public Primitive {
    private:
        Vector3 center;
        double radius;
        double radius2;
    public:
        Sphere(Vector3 center, double radius, Material *material);
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
};

#endif