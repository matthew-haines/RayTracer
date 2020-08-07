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
        double Intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
        Vector3 Sample(double u1, double u2, double& probability);
        Vector3 DirectionalSample(double u1, double u2, Vector3 point, double& probability);
};

#endif