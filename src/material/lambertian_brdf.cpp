#include "lambertian_brdf.hpp"
#include "../matrix3.hpp"
#include "../helpers.hpp"

LambertianBRDF::LambertianBRDF(double albedo): BxDF(false), albedo(albedo) {}

Vector3 LambertianBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    return albedo / M_PI;
}

Vector3 LambertianBRDF::Sample(Vector3 in, Vector3 normal) {
    double u1 = dist(gen);
    double u2 = dist(gen);
    Matrix3 rotation = Matrix3::createFromNormal(normal); // convert (0, 0, 1) to normal
    Vector3 temp = CosineSampleHemisphere::sample(u1, u2); // (around (0, 0, 1))
    return rotation * temp;
}

double LambertianBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return CosineSampleHemisphere::pdf(normal.dot(out));
}

Vector3 LambertianBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    out = Sample(in, normal);
    probability = pdf(in, normal, out);
    return Evaluate(in, normal, out);
}