#include "microfacet.hpp"
#include "../helpers.hpp"
#include <cmath>
// http://www.cs.cornell.edu/%7Esrm/publications/EGSR07-btdf.pdf

BeckmannDistribution::BeckmannDistribution(double alpha): alpha(alpha), alpha2(square(alpha)) {

}

double BeckmannDistribution::Distribution(Vector3 m, Vector3 n) {
    double mdotn = m.dot(n);
    double theta = std::acos(mdotn);
    return PositiveCharacteristic(mdotn) / (M_PI * alpha2 * square(square(mdotn))) * std::exp(-square(std::tan(theta))/alpha2);
}

double BeckmannDistribution::Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n) {
    auto g1 = [this](Vector3 v, Vector3 m, Vector3 n) {
        double vdotn = v.dot(n);
        double thetav = std::acos(vdotn);
        double a = 1 / (alpha * std::tan(thetav));
        //return PositiveCharacteristic(v.dot(m) / vdotn) * 2 / (1 + std::erf(a) + 1 / (a * std::sqrt(M_PI)) * std::exp(-square(a)));
        // Above is the actual G1, the one below is a fit
        return PositiveCharacteristic(v.dot(m)/vdotn) * a < 1.6 ? (3.535 * a + 2.181 * square(a)) / (1 + 2.276 * a + 2.577 * square(a)) : 1;
    };
    return g1(i, m, n) * g1(o, m, n);
}

Vector3 BeckmannDistribution::Sample(double e1, double e2) {
    return SphericalToCartesian(Vector3(1, 2 * M_PI * e1, std::atan(std::sqrt(-alpha2 * std::log(1 - e2)))));
}

PhongDistribution::PhongDistribution(double alpha): alpha(alpha) {

}

double PhongDistribution::Distribution(Vector3 m, Vector3 n) {
    double mdotn = m.dot(n);
    return PositiveCharacteristic(mdotn) * (alpha + 2) / (2 * M_PI) * std::pow(mdotn, alpha);
}

double PhongDistribution::Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n) {
    auto g1 = [this](Vector3 v, Vector3 m, Vector3 n) {
        double vdotn = v.dot(n);
        double thetav = std::acos(vdotn);
        double a = std::sqrt(0.5 * alpha + 1) / std::tan(thetav);
        //return PositiveCharacteristic(v.dot(m) / vdotn) * 2 / (1 + std::erf(a) + 1 / (a * std::sqrt(M_PI)) * std::exp(-square(a)));
        // Above is the actual G1, the one below is a fit
        return PositiveCharacteristic(v.dot(m)/vdotn) * a < 1.6 ? (3.535 * a + 2.181 * square(a)) / (1 + 2.276 * a + 2.577 * square(a)) : 1;
    };
    return g1(i, m, n) * g1(o, m, n);
}

Vector3 PhongDistribution::Sample(double e1, double e2) {
    return SphericalToCartesian(Vector3(1, 2 * M_PI * e1, std::acos(std::pow(e2, 1 / (alpha + 2)))));
}

GGXDistribution::GGXDistribution(double alpha): alpha(alpha), alpha2(square(alpha)) {

}

double GGXDistribution::Distribution(Vector3 m, Vector3 n) {
    double mdotn = m.dot(n);
    double theta = std::acos(mdotn);
    return alpha2 * PositiveCharacteristic(mdotn) / (M_PI * square(square(mdotn)) * square(alpha2 + square(std::tan(theta))));
}

double GGXDistribution::Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n) {
    auto g1 = [this](Vector3 v, Vector3 m, Vector3 n) {
        double vdotn = v.dot(n);
        double thetav = std::acos(vdotn);
        return PositiveCharacteristic(v.dot(m) / vdotn) * 2 / (1 + std::sqrt(1 + alpha2 * square(std::tan(thetav))));
    };
    return g1(i, m, n) * g1(o, m, n);
}

Vector3 GGXDistribution::Sample(double e1, double e2) {
    return SphericalToCartesian(Vector3(1, 2 * M_PI * e1, std::atan(alpha * std::sqrt(e2) / std::sqrt(1 - e2))));
}