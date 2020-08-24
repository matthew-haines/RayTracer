#include "fresnel.hpp"
#include "../helpers.hpp"
#include <cmath>

double FresnelDielectric(double ndoti, double refractionIndex) {
    double c = ndoti;
    double g = square(refractionIndex) - 1 + square(c);
    if (g < 0) {
        return 1;
    } else {
        g = std::sqrt(g);
    }
    return 0.5 * square(g - c) / square(g + c) * (1 + square(c * (g + c) - 1) / square(c * (g - c) + 1));
}