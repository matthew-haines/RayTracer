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
        Vector3 sample(double u1, double u2);
        double samplePdf(Vector3 point, Vector3 direction);
        Vector3 directionalSample(double u1, double u2, Vector3 point);
        double directionalSamplePdf(Vector3 point, Vector3 direction);
        Bound getBound();
};

#endif