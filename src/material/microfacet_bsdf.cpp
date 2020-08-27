#include "microfacet_bsdf.hpp"
#include "../helpers.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include <cmath>

MicrofacetBSDF::MicrofacetBSDF(double refractionIndex, Fresnel* fresnelFunction, MicrofacetDistribution* microfacetDistribution): BxDF(false), refractionIndex(refractionIndex), fresnelFunction(fresnelFunction), microfacetDistribution(microfacetDistribution) {}

Vector3 MicrofacetBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    Vector3 hr = (std::copysign(1.0, normal.dot(-in)) * (out - in)).normalized();
    double reflectFresnel;
    double geometry;
    double distribution;
    double reflectionTerm = reflectFresnel * geometry * distribution / (4 * std::abs(normal.dot(-in) * normal.dot(out)));

    double refractFresnel;
    double refractGeom;
    //Vector3 ht = -()
}

Vector3 MicrofacetBSDF::Sample(Vector3 in, Vector3 normal) {
    double fresnel = (*fresnelFunction)(-in.dot(normal), 1, refractionIndex);
    Vector3 m = Matrix3::createFromNormal(normal) * microfacetDistribution->Sample(dist(gen), dist(gen));
    double u = dist(gen);
    if (u < fresnel) {
        // Reflect
        return SpecularReflectBRDF::GetReflection(in, m);
    } else {
        // Transmit
        return SpecularRefractBTDF::GetRefraction(in, m, refractionIndex);
    }
}

double MicrofacetBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    Vector3 m = (out - in).normalized();
    return microfacetDistribution->Evaluate(m, normal) * m.dot(normal);
}

Vector3 MicrofacetBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    
}