#include "specular_refract_btdf.hpp"
#include "specular_reflect_brdf.hpp"
#include "../helpers.hpp"
#include <cmath>

SpecularRefractBTDF::SpecularRefractBTDF(double refractionIndex): BxDF(true), refractionIndex(refractionIndex) {}

Vector3 SpecularRefractBTDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    return Vector3(1.);
}

Vector3 SpecularRefractBTDF::Sample(Vector3 in, Vector3 normal) {
    return GetRefraction(in, normal, refractionIndex);
}

Vector3 SpecularRefractBTDF::GetRefraction(Vector3 in, Vector3 normal, double refractionIndex) {
    double ndoti = normal.dot(in);
    double eta = 1 / refractionIndex;
    if (ndoti > 0) {
        eta = 1 / eta;
        normal = -normal;
    } else {
        ndoti = -ndoti;
    }
    double ndott2 = 1 - square(eta) * (1-square(ndoti));
    if (ndott2 < 0) {
        return SpecularReflectBRDF::GetReflection(in, ndoti < 0 ? -normal : normal);
    }
    return (eta * in + (eta * ndoti - std::sqrt(ndott2)) * normal).normalized();
}

double SpecularRefractBTDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return 1.;
}

Vector3 SpecularRefractBTDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = Sample(in, normal);
    probability = pdf(in, normal, out);
    return Evaluate(in, normal, out);
}