#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "primitive.hpp"
#include "../vector3.hpp"

class Triangle: public Primitive {
    private:
        Vector3 v0, v1, v2;
        bool normals;
        Vector3 vn0, vn1, vn2;
        Vector3 planeNormal, e1, e2;
        double area;
    public:
        Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material, bool normals=false, Vector3 vn0 = Vector3(0.), Vector3 vn1 = Vector3(0.), Vector3 vn2 = Vector3(0.));
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
        Vector3 sample(double u1, double u2);
        double samplePdf(Vector3 point, Vector3 direction);
        Vector3 directionalSample(double u1, double u2, Vector3 point);
        double directionalSamplePdf(Vector3 point, Vector3 direction);
        Bound getBound();
};

#endif
