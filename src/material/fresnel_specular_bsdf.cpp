#include "fresnel_specular_bsdf.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include "fresnel.hpp"
#include "../helpers.hpp"

FresnelSpecularBSDF::FresnelSpecularBSDF(double refractionIndex): BxDF(true), refractionIndex(refractionIndex) {}

Vector3 FresnelSpecularBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    // not needed 
    return Vector3(0.);
}

Vector3 FresnelSpecularBSDF::Sample(Vector3 in, Vector3 normal) {
    // not needed
    return 0;
}

double FresnelSpecularBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    // not needed
    return 0;
}

Vector3 FresnelSpecularBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    double fresnel = FresnelDielectric(normal.dot(in), refractionIndex, 1);
    Vector3 f = Vector3(1);
    if (dist(gen) < fresnel) {
        out = SpecularReflectBRDF::GetReflection(in, normal);
    } else {
        out = SpecularRefractBTDF::GetRefraction(in, normal, refractionIndex);
    }
    probability = 1; // no need to importance sample
    return f;
}