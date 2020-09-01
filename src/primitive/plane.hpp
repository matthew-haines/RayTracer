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
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
        Vector3 sample(double u1, double u2);
        double samplePdf(Vector3 point, Vector3 direction);
        Vector3 directionalSample(double u1, double u2, Vector3 point);
        double directionalSamplePdf(Vector3 point, Vector3 direction);
        Bound getBound();
};

#endif