#include "fresnel_specular_bsdf.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include "fresnel.hpp"

FresnelSpecularBSDF::FresnelSpecularBSDF(double refractionIndex): BxDF(true), refractionIndex(refractionIndex) {}

Vector3 FresnelSpecularBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    
}

Vector3 FresnelSpecularBSDF::Sample(Vector3 in, Vector3 normal) {

}

double FresnelSpecularBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {

}

Vector3 FresnelSpecularBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    double fresnel = FresnelDielectric(normal.dot(-in), refractionIndex);
    if (dist(gen) < fresnel) {
        probability = fresnel;
        out = SpecularReflectBRDF::GetReflection(in, normal);
    } else {
        probability = 1 - fresnel;
        out = SpecularRefractBTDF::GetRefraction(in, normal, refractionIndex);
    }
    return Vector3(probability);
}