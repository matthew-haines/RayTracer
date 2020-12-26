#include "lambertian_brdf.hpp"
#include "matrix3.hpp"
#include "helpers.hpp"

LambertianBRDF::LambertianBRDF(const double albedo): BxDF(false), albedo(albedo) {}

Vector3 LambertianBRDF::evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return albedo / M_PI;
}

Vector3 LambertianBRDF::sample(const Vector3 in, const Vector3 normal) {
    double u1 = dist(gen);
    double u2 = dist(gen);
    Matrix3 rotation = Matrix3::createFromNormal(normal); // convert (0, 0, 1) to normal
    Vector3 temp = CosineSampleHemisphere::sample(u1, u2); // (around (0, 0, 1))
    return rotation * temp;
}

double LambertianBRDF::pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const {
    return CosineSampleHemisphere::pdf(normal.dot(out));
}

Vector3 LambertianBRDF::operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability) {
    out = sample(in, normal);
    probability = pdf(in, normal, out);
    return evaluate(in, normal, out);
}