#ifndef SPECULAR_REFRACT_BTDF_HPP
#define SPECULAR_REFRACT_BTDF_HPP

#include "bxdf.hpp"

// Simple refraction BTDF, no fresnel.
class SpecularRefractBTDF: public BxDF {
    private:
        const double refractionIndex;
    public:
        SpecularRefractBTDF(const double refractionIndex);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        static Vector3 getRefraction(const Vector3 in, const Vector3 normal, const double refractionIndex);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif