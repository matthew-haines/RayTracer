#include "fresnel.hpp"
#include "helpers.hpp"
#include <cmath>

double FresnelDielectric(double ndoti, double etaT, double etaI) {
    if (ndoti < 0) {
        std::swap(etaT, etaI);
    }
    double cosI = std::abs(ndoti);
    double sinI = std::sqrt(std::max((double)0, 1 - square(cosI)));
    double cosT = std::sqrt(std::max((double)0, 1 - square(sinI * etaI / etaT)));
    // https://en.wikipedia.org/wiki/Fresnel_equations equation 38
    double rs = (etaT * cosI - etaI * cosT)/(etaT * cosI + etaI * cosT);
    double rt = (etaI * cosI - etaT * cosT)/(etaI * cosI + etaT * cosT);
    return 0.5 * (square(rs) + square(rt));
}

double DielectricFresnel::operator()(double cosI, double etaT, double etaI) const {
    if (cosI < 0) {
        std::swap(etaT, etaI);
        cosI = std::abs(cosI);
    }
    double sinI = std::sqrt(std::max((double)0, 1 - square(cosI)));
    double sinT = etaI / etaT * sinI;
    if (sinT >= 1) return 1;
    double cosT = std::sqrt(1 - square(sinT));
    // https://en.wikipedia.org/wiki/Fresnel_equations equation 38
    double rs = square((etaT * cosI - etaI * cosT)/(etaT * cosI + etaI * cosT));
    double rt = square((etaI * cosI - etaT * cosT)/(etaI * cosI + etaT * cosT));
    return 0.5 * (square(rs) + square(rt));
}

double ReflectanceFresnel::operator()(double cosI, double etaT, double etaI) const {
    return 1;
}

double TransmittanceFresnel::operator()(double cosI, double etaT, double etaI) const {
    return 0;
}

double FixedFresnel::operator()(double cosI, double etaT, double etaI) const {
    return ratio;
}