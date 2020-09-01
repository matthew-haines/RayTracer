#ifndef HELPERS_HPP
#define HELPERS_HPP
#include "vector2.hpp"
#include "vector3.hpp"
#include <cmath>
#include <functional>
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

double sign(double x);

char colorToChar(double color);

struct UniformSampleHemisphere {
    static Vector3 sample(double u1, double u2);
    static double pdf(Vector3 v);
};

struct UniformSampleSphere {
    static Vector3 sample(double u1, double u2);
    static double pdf();
};

struct UniformSampleCone {
    static Vector3 sample(double u1, double u2, Vector3 direction, double thetaMax);
    static double pdf(double cosThetaMax);
};

struct ConcentricSampleDisk {
    static Vector2 sample(double u1, double u2);
    static double pdf(Vector2 v);
};

struct CosineSampleHemisphere {
    static Vector3 sample(double u1, double u2);
    static double pdf(double cosTheta);
};

void parallelizeLoop(int threads, std::function<void(int)> func, int range, bool showProgress=false);

double powerHeuristic(double a, double b);

double positiveCharacteristic(double a);

#endif