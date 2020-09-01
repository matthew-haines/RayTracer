#include "specular_reflect_brdf.hpp"
#include "fresnel.hpp"

SpecularReflectBRDF::SpecularReflectBRDF(): BxDF(true) {}

Vector3 SpecularReflectBRDF::evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    return Vector3(1);
}

Vector3 SpecularReflectBRDF::sample(Vector3 in, Vector3 normal) {
    return getReflection(in, normal);
}

Vector3 SpecularReflectBRDF::getReflection(Vector3 in, Vector3 normal) {
    return in + 2 * in.dot(-normal) * normal;
}

double SpecularReflectBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return 1.;
}

Vector3 SpecularReflectBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = sample(in, normal);
    probability = pdf(in, normal, out);
    return evaluate(in, normal, out);
}