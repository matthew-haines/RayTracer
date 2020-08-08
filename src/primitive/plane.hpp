#ifndef PLANE_HPP
#define PLANE_HPP
#include "primitive.hpp"
#include <vector>

class Plane: public Primitive {
    protected:
        // Ax + Bx + Cx + D = 0
        Vector3 planeNormal;
        double d;
        bool oneSided;
    public:
        Plane(Vector3 planeNormal, double d, Material *material, bool oneSided=true);
        double Intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
        Vector3 Sample(double u1, double u2);
        double SamplePDF(Vector3 point, Vector3 direction);
        Vector3 DirectionalSample(double u1, double u2, Vector3 point);
        double DirectionalSamplePDF(Vector3 point, Vector3 direction);
};

#endif