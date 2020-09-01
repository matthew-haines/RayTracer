#ifndef MICROFACET_BSDF_HPP 
#define MICROFACET_BSDF_HPP
#include "bxdf.hpp"
#include "fresnel.hpp"
#include "microfacet.hpp"

class MicrofacetBSDF: public BxDF {
    private:
        double refractionIndex;
        Fresnel* fresnelFunction;
        MicrofacetDistribution* microfacetDistribution;
    public:
        MicrofacetBSDF(double refractionIndex, Fresnel* fresnelFunction, MicrofacetDistribution* microfacetDistribution);
        Vector3 evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif