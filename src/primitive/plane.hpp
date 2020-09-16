#ifndef PLANE_HPP
#define PLANE_HPP

#include "primitive.hpp"
#include <vector>

class Plane: public Primitive {
    protected:
        // Ax + Bx + Cx + D = 0
        const Vector3 planeNormal;
        const double d;
        const bool oneSided;
    public:
        Plane(const Vector3 planeNormal, const double d, Material* const material, const bool oneSided=true);
        double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const;
        Vector3 sample(const double u1, const double u2) const;
        double samplePdf(const Vector3 point, const Vector3 direction) const;
        Vector3 directionalSample(const double u1, const double u2, const Vector3 point) const;
        double directionalSamplePdf(const Vector3 point, const Vector3 direction) const;
        Bound getBound() const;
        Vector2 getUVAtPoint(const Vector3& point) const;
};

#endif