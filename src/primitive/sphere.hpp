#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "material.hpp"
#include "primitive.hpp"

class Sphere: public Primitive {
    private:
        const Vector3 center;
        const double radius;
        const double radius2;
    public:
        Sphere(const Vector3 center, const double radius, const Material material);
        double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const;
        Vector3 sample(const double u1, const double u2) const;
        double samplePdf(const Vector3 point, const Vector3 direction) const;
        Vector3 directionalSample(const double u1, const double u2, const Vector3 point) const;
        double directionalSamplePdf(const Vector3 point, const Vector3 direction) const;
        Bound getBound() const;
        Vector2 getUVAtPoint(const Vector3& point) const;
};

#endif