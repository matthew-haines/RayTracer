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
    Matrix3 rotation = Matrix3::createFromNormal(normal);
    double NdotL;
    Vector3 out;
    out = rotation * CosineSampleHemisphere::sample(u1, u2);
    return out;
}

double LambertianBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    return CosineSampleHemisphere::pdf(normal.dot(out));
}
