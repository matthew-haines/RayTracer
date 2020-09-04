#include "specular_reflect_brdf.hpp"
#include "fresnel.hpp"

SpecularReflectBRDF::SpecularReflectBRDF(): BxDF(true) {}

Vector3 SpecularReflectBRDF::evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return Vector3(1);
}

Vector3 SpecularReflectBRDF::sample(const Vector3 in, const Vector3 normal) {
    return getReflection(in, normal);
}

Vector3 SpecularReflectBRDF::getReflection(const Vector3 in, const Vector3 normal) {
    return in + 2 * in.dot(-normal) * normal;
}

double SpecularReflectBRDF::pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return 1.;
}

Vector3 SpecularReflectBRDF::operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability) {
    out = sample(in, normal);
    probability = pdf(in, normal, out);
    return evaluate(in, normal, out);
}