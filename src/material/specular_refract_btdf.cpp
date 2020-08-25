#include "specular_refract_btdf.hpp"
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
    double ndoti = std::clamp(normal.dot(-in), -1., 1.);
    double eta = 1 / refractionIndex;
    if (ndoti < 0) {
        eta = 1 / eta;
    } else {
        ndoti = -ndoti;
    }
    double term = 1 - square(eta) * (1-square(ndoti));
    return (eta * in + (eta * ndoti - std::sqrt(term)) * normal);
}

double SpecularRefractBTDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return 1.;
}

Vector3 SpecularRefractBTDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = Sample(in, normal);
    probability = pdf(in, normal, out);
    return Evaluate(in, normal, out);
}