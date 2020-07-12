#include "lambertian_brdf.hpp"
#include "../matrix3.hpp"
#include "../helpers.hpp"

LambertianBRDF::LambertianBRDF(double albedo): BxDF(), albedo(albedo) {}
Vector3 LambertianBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3& out, double& probability, bool importanceSample) {
    double u1 = dist(gen);
    double u2 = dist(gen);
    Matrix3 rotation = Matrix3::createFromNormal(normal);
    double NdotL;
    if (importanceSample) {
        out = rotation * CosineSampleHemisphere::sample(u1, u2);
        NdotL = normal.dot(out);
        probability = CosineSampleHemisphere::pdf(NdotL);
    }
    else {
        out = rotation * UniformSampleHemisphere::sample(u1, u2);
        probability = UniformSampleHemisphere::pdf(out);
    }
    return albedo / M_PI;
}