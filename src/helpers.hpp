#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "vector2.hpp"
#include "vector3.hpp"
#include "matrix3.hpp"
#include <functional>

// Need to define these in header
template <typename T>
T mix(const T x, const T y, const double a) {
    return x * (1. - a) + y * a;
}

template <typename T>
T square(const T x) {
    return x * x;
}

double sign(const double x);

char colorToChar(const double color);

double charToColor(const unsigned char color);

struct UniformSampleHemisphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf(const Vector3 v);
};

struct UniformSampleSphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf();
};

struct UniformSampleCone {
    static Vector3 sample(const double u1, const double u2, const Vector3 direction, const double thetaMax);
    static double pdf(const double cosThetaMax);
};

struct ConcentricSampleDisk {
    static Vector2 sample(double u1, double u2);
    static double pdf();
};

struct CosineSampleHemisphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf(const double cosTheta);
};

void parallelizeLoop(const int threads, const std::function<void(int)> func, const int range, const bool showProgress=false);

double powerHeuristic(const double a, const double b);

double positiveCharacteristic(const double a);

#endif