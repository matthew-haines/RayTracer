#include "specular_reflect_brdf.hpp"

SpecularReflectBRDF::SpecularReflectBRDF(): BxDF(true) {}

Vector3 SpecularReflectBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    return Vector3(1.);
}

Vector3 SpecularReflectBRDF::Sample(Vector3 in, Vector3 normal) {
    return GetReflection(in, normal);
}

Vector3 SpecularReflectBRDF::GetReflection(Vector3 in, Vector3 normal) {
    return in + 2 * in.dot(-normal) * normal;
}

double SpecularReflectBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return 1.;
}

Vector3 SpecularReflectBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = Sample(in, normal);
    probability = pdf(in, normal, out);
    return Evaluate(in, normal, out);
}