#ifndef SPECULAR_REFLECT_BRDF_HPP
#define SPECULAR_REFLECT_BRDF_HPP

#include "bxdf.hpp"

// Simple reflection BRDF, no fresnel effect.
class SpecularReflectBRDF: public BxDF {
    public:
        SpecularReflectBRDF();
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        static Vector3 getReflection(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif