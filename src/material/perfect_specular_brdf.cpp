#include "perfect_specular_brdf.hpp"

PerfectSpecularBRDF::PerfectSpecularBRDF(): BxDF(true) {}

Vector3 PerfectSpecularBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    return Vector3(1.);
}

Vector3 PerfectSpecularBRDF::Sample(Vector3 in, Vector3 normal) {
    return in + 2 * in.dot(-normal) * normal;
}

double PerfectSpecularBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return 1.;
}

Vector3 PerfectSpecularBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = Sample(in, normal);
    probability = pdf(in, normal, out);
    return Evaluate(in, normal, out);
}