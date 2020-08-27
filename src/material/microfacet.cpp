#include "microfacet.hpp"
#include "../helpers.hpp"
#include <cmath>
// http://www.cs.cornell.edu/%7Esrm/publications/EGSR07-btdf.pdf

BeckmannDistribution::BeckmannDistribution(double alpha): alpha(alpha), alpha2(square(alpha)) {

}

double BeckmannDistribution::Evaluate(Vector3 m, Vector3 n) {
    double mdotn = m.dot(n);
    double theta = std::acos(mdotn);
    double distTerm = PositiveCharacteristic(mdotn) / (M_PI * alpha2 * square(square(mdotn))) * std::exp(-square(std::tan(theta))/alpha2);
    double smithG = 
}

double BeckmannDistribution::G1(Vector3 v, Vector3 m, Vector3 n) {
    double vdotn = v.dot(n);
    double thetav = std::acos(vdotn);
    double a = 1 / (alpha * std::tan(thetav));
    //return PositiveCharacteristic(v.dot(m) / vdotn) * 2 / (1 + std::erf(a) + 1 / (a * std::sqrt(M_PI)) * std::exp(-square(a)));
    // Above is the actual G1, the one below is a fit
    return PositiveCharacteristic(v.dot(m)/vdotn) * a < 1.6 ? (3.535 * a + 2.181 * square(a)) / (1 + 2.276 * a + 2.577 * square(a)) : 1;
}

Vector3 BeckmannDistribution::Sample(double e1, double e2) {
    return SphericalToCartesian(1, 2 * M_PI * e1, std::atan(std::sqrt(-alpha2 * std::log(1 - e2))));
}

double PhongDistribution::Evaluate(Vector3 m, Vector3 n) {
    double mdotn = m.dot(n);
    return P
}