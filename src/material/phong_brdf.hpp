#ifndef PHONG_BRDF_HPP
#define PHONG_BRDF_HPP

#include "bxdf.hpp"

// Implementation of the Phong shading model as a BRDF.
class PhongBRDF: public BxDF {
    private:
        const double kd;
        const double ks;
        const double n;
    public:
        PhongBRDF(const double kd, const double ks, const double n);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif