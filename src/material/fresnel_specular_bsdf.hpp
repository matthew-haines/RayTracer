#ifndef FRESNEL_SPECULAR_BSDF_HPP
#define FRESNEL_SPECULAR_BSDF_HPP

#include "bxdf.hpp"

class FresnelSpecularBSDF: public BxDF {
    private:
        const double refractionIndex;
    public:
        FresnelSpecularBSDF(const double refractionIndex);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif
