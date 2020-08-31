#include "phong_brdf.hpp"
#include "../helpers.hpp"
#include "specular_reflect_brdf.hpp"
#include <cmath>

PhongBRDF::PhongBRDF(double kd, double ks, double n): BxDF(false), kd(kd), ks(ks), n(n) {}

Vector3 PhongBRDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    double calpha = std::clamp(SpecularReflectBRDF::GetReflection(in, normal).dot(out), -1., 1.);
    if (normal.dot(out) < 0) {
        return 0;
    } else {
        return M_1_PI * (kd + ks * (n + 2) / 2 * std::pow(calpha, n));
    }
}

Vector3 PhongBRDF::Sample(Vector3 in, Vector3 normal) {
    double u = dist(gen);
    double u1 = dist(gen);
    double u2 = dist(gen);
    if (u < kd) {
        //diffuse
        Matrix3 rotation = Matrix3::createFromNormal(normal); // convert (1, 0, 0) to normal
        Vector3 vec = CosineSampleHemisphere::sample(u1, u2); // (around (0, 0, 1))
        return rotation * vec;
    } else if (u < kd + ks) {
        //specular
        Vector3 vec = SphericalToCartesian(Vector3(1, 2 * M_PI * u1, std::acos(std::pow(u2, 1 / (n+1)))));
        Matrix3 rotation = Matrix3::createFromNormal(SpecularReflectBRDF::GetReflection(in, normal));
        return rotation * vec;
    } else {
        return 0;
    }
}
double PhongBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    // weight probabilities
    double calpha = std::clamp(SpecularReflectBRDF::GetReflection(in, normal).dot(out), -1., 1.);
    return kd * CosineSampleHemisphere::pdf(normal.dot(out)) + ks * 0.5 * M_1_PI * (n + 1) * std::pow(calpha, n);
}

Vector3 PhongBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    double u = dist(gen);
    double u1 = dist(gen);
    double u2 = dist(gen);
    double calpha;
    Vector3 reflect = SpecularReflectBRDF::GetReflection(in, normal);
    if (u < kd) {
        //diffuse
        Matrix3 rotation = Matrix3::createFromNormal(normal); // convert (1, 0, 0) to normal
        Vector3 temp = CosineSampleHemisphere::sample(u1, u2); // (around (0, 0, 1))
        out = rotation * temp;
        calpha = out.dot(reflect);
    } else if (u < kd + ks) {
        //specular
        calpha = std::pow(u2, 1/(n+1));
        Vector3 vec = SphericalToCartesian(Vector3(1, 2 * M_PI * u1, std::acos(calpha)));
        Matrix3 rotation = Matrix3::createFromNormal(reflect);
        out = rotation * vec;
    } else {
        probability = 1;
        out = Vector3(0);
        return 0;
    }
    probability = kd * CosineSampleHemisphere::pdf(normal.dot(out)) + ks * 0.5 * M_1_PI * (n + 1) * std::pow(calpha, n);
    if (normal.dot(out) < 0) {
        return 0;
    }
    return M_1_PI * (kd + ks * (n + 2) / 2 * std::pow(calpha, n));
}