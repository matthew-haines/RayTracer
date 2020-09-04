#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "primitive.hpp"

class Triangle: public Primitive {
    private:
        const Vector3 v0, v1, v2;
        const bool normals;
        const Vector3 vn0, vn1, vn2;
        Vector3 planeNormal, e1, e2;
        double area;
    public:
        Triangle(const Vector3 v0, const Vector3 v1, const Vector3 v2, Material* const material, const bool normals=false, const Vector3 vn0 = Vector3(0.), const Vector3 vn1 = Vector3(0.), const Vector3 vn2 = Vector3(0.));
        double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const;
        Vector3 sample(const double u1, const double u2) const;
        double samplePdf(const Vector3 point, const Vector3 direction) const;
        Vector3 directionalSample(const double u1, const double u2, const Vector3 point) const;
        double directionalSamplePdf(const Vector3 point, const Vector3 direction) const;
        Bound getBound() const;
};

#endif
