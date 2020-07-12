#include "perfect_specular_brdf.hpp"

PerfectSpecularBRDF::PerfectSpecularBRDF() {}

Vector3 PerfectSpecularBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3& out, double& probability, bool importanceSample) {
    probability = 1;
    out = -in + 2 * in.dot(normal) * normal;
    return Vector3(1., 1., 1.);
}
