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
    double fresnel = FresnelDielectric(normal.dot(-in), refractionIndex, 1);
    if (dist(gen) < fresnel) {
        return SpecularReflectBRDF::GetReflection(in, normal);
    } else {
        return SpecularRefractBTDF::GetRefraction(in, normal, refractionIndex);
    }
}

double FresnelSpecularBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    // not needed
    double fresnel = FresnelDielectric(normal.dot(-in), refractionIndex, 1);
    if (out == SpecularReflectBRDF::GetReflection(in, normal)) {
        return fresnel;
    } else {
        return 1 - fresnel;
    }
}

Vector3 FresnelSpecularBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    double fresnel = FresnelDielectric(normal.dot(in), refractionIndex, 1);
    Vector3 f = Vector3(1) / normal.dot(out);
    if (dist(gen) < fresnel) {
        probability = fresnel;
        out = SpecularReflectBRDF::GetReflection(in, normal);
    } else {
        probability = 1 - fresnel;
        out = SpecularRefractBTDF::GetRefraction(in, normal, refractionIndex);
    }
    return f;
}