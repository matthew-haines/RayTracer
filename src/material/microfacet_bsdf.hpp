#ifndef MICROFACET_BSDF_HPP 
#define MICROFACET_BSDF_HPP

#include "bxdf.hpp"
#include "fresnel.hpp"
#include "microfacet.hpp"

// Base class for any microfacet BSDF, fresnel and the microfacet distribution can be mixed and matched.
class MicrofacetBSDF: public BxDF {
    private:
        const double refractionIndex;
        Fresnel* const fresnelFunction;
        MicrofacetDistribution* const microfacetDistribution;
    public:
        MicrofacetBSDF(const double refractionIndex, Fresnel* const fresnelFunction, MicrofacetDistribution* const microfacetDistribution);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif