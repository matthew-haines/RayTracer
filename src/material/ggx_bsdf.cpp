#include "ggx_bsdf.hpp"
#include "../helpers.hpp"
#include <cmath>

GGXBSDF::GGXBSDF(double alpha, double albedo, double refractionIndex, double transmittanceProbability): BxDF(false), alpha(alpha), alpha2(square(alpha)), albedo(albedo), refractionIndex(refractionIndex), transmittanceProbability(transmittanceProbability) {}

Vector3 GGXBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    Vector3 hr = (std::copysign(1.0, normal.dot(-in)) * (out - in)).normalized();
    double reflectFresnel;
    double geometry;
    double distribution;
    double reflectionTerm = reflectFresnel * geometry * distribution / (4 * std::abs(normal.dot(-in) * normal.dot(out)));

    double refractFresnel;
    double refractGeom;
    //Vector3 ht = -()
}

Vector3 GGXBSDF::Sample(Vector3 in, Vector3 normal) {
    double e1 = dist(gen);
    double e2 = dist(gen);
    double theta = std::atan(alpha * std::sqrt(e1) / (std::sqrt(1-e1)));
    double phi = 2 * M_PI * e2;

}

double GGXBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {

}

Vector3 GGXBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    double e1 = dist(gen);
    double e2 = dist(gen);
    double theta = std::atan(alpha * std::sqrt(e1) / (std::sqrt(1-e1)));
    double phi = 2 * M_PI * e2;

    Vector3 m = Matrix3::createFromNormal(normal) * SphericalToCartesian(Vector3(1.0, phi, theta));

    double mdotn = m.dot(normal);
    double distributionTerm = alpha2 * (mdotn > 0 ? 1 : 0) / (M_PI * square(square(std::cos(theta))) * square((alpha2 + square(std::tan(theta)))));

}