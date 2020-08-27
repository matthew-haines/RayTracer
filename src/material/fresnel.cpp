#include "fresnel.hpp"
#include "../helpers.hpp"
#include <cmath>

double FresnelDielectric(double ndoti, double etaT, double etaI) {
    std::clamp(ndoti, -1., 1.);
    bool entering = ndoti < 0;
    if (!entering) {
        std::swap(etaT, etaI);
    }
    ndoti = std::abs(ndoti);
    // https://en.wikipedia.org/wiki/Fresnel_equations equation 38
    double rs = square((etaT * ndoti + etaI * ndoti)/(3));
    return 1;
}