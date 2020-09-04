#include "specular_refract_btdf.hpp"
#include "specular_reflect_brdf.hpp"
#include "../helpers.hpp"
#include <cmath>

SpecularRefractBTDF::SpecularRefractBTDF(const double refractionIndex): BxDF(true), refractionIndex(refractionIndex) {}

Vector3 SpecularRefractBTDF::evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return Vector3(1);
}

Vector3 SpecularRefractBTDF::sample(const Vector3 in, const Vector3 normal) {
    return getRefraction(in, normal, refractionIndex);
}

Vector3 SpecularRefractBTDF::getRefraction(const Vector3 in, const Vector3 tempnormal, const double refractionIndex) {
    Vector3 normal = tempnormal;
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
        return SpecularReflectBRDF::getReflection(in, ndoti < 0 ? -normal : normal);
    }
    return (eta * in + (eta * ndoti - std::sqrt(ndott2)) * normal).normalized();
}

double SpecularRefractBTDF::pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return 1.;
}

Vector3 SpecularRefractBTDF::operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability) {
    out = sample(in, normal);
    probability = pdf(in, normal, out);
    return evaluate(in, normal, out);
}