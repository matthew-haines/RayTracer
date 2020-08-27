#include "fresnel.hpp"
#include "../helpers.hpp"
#include <cmath>

double FresnelDielectric(double ndoti, double etaT, double etaI) {
    bool entering = ndoti < 0;
    if (!entering) {
        std::swap(etaT, etaI);
    }
    double cosI = std::abs(ndoti);
    double cosT = std::sqrt(1 - square(std::sqrt(1-square(cosI)) * etaI / etaT));
    // https://en.wikipedia.org/wiki/Fresnel_equations equation 38
    double rs = square((etaT * cosI - etaI * cosT)/(etaT * cosI + etaI * cosT));
    double rt = square((etaI * cosI - etaT * cosT)/(etaI * cosI + etaT * cosT));
    return 0.5 * (square(rs) + square(rt));
}