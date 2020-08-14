#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "primitive.hpp"
#include "../vector3.hpp"

class Triangle: public Primitive {
    private:
        Vector3 v0, v1, v2;
        Vector3 planeNormal, e1, e2;
    public:
        Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material);
        double Intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
        Vector3 Sample(double u1, double u2);
        double SamplePDF(Vector3 point, Vector3 direction);
        Vector3 DirectionalSample(double u1, double u2, Vector3 point);
        double DirectionalSamplePDF(Vector3 point, Vector3 direction);
        Bound GetBound();
};

#endif
