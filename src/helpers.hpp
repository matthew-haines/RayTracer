#ifndef HELPERS_HPP
#define HELPERS_HPP
#include "vector3.hpp"
#include <cmath>
#include <random>

// Need to define these in header
template <typename T>
T mix(T x, T y, double a) {
    return x * (1. - a) + y * a;
}

template <typename T>
T square(T x) {
    return x * x;
}

double sign(double x) {
    if (x > 0) return 1;
    else if (x = 0) return 0;
    return -1;
}

namespace sample {
    Vector3 UniformSampleHemisphere(double u1, double u2) {
        double z = u1;
        double r = std::sqrt(std::max(0., 1. - z * z));
        double phi = 2 * M_PI * u2;
        return Vector3(r * std::cos(phi), r * std::sin(phi), z);
    }

    Vector3 CosineSampleHemisphere() {

    }
}

#endif