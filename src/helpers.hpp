#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "vector2.hpp"
#include "vector3.hpp"
#include "matrix3.hpp"
#include <functional>
#include <stdint.h>
#include <random>

// Need to define these in header

// Mixes two values given a weighting a.
template <typename T>
T mix(const T x, const T y, const double a) {
    return x * (1. - a) + y * a;
}

template <typename T>
T square(const T x) {
    return x * x;
}

// sgn(x)
double sign(const double x);

char colorToChar(const double color);

double charToColor(const unsigned char color);

// Samples hemisphere around (0, 0, 1)
struct UniformSampleHemisphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf(const Vector3 v);
};

struct UniformSampleSphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf();
};

// Samples cone of directions given a maximum angle from a direction.
struct UniformSampleCone {
    static Vector3 sample(const double u1, const double u2, const Vector3 direction, const double thetaMax);
    static double pdf(const double cosThetaMax);
};

// Samples point on unit disk given args in [0, 1)
struct ConcentricSampleDisk {
    static Vector2 sample(double u1, double u2);
    static double pdf();
};

// Samples hemisphere around (0, 0, 1) with cosine weighting.
struct CosineSampleHemisphere {
    static Vector3 sample(const double u1, const double u2);
    static double pdf(const double cosTheta);
};

// Takes threads and function to apply at each iteration of loop, function takes index
void parallelizeLoop(const int threads, const std::function<void(int)> func, const int range, const bool showProgress=false);

// Power heurstic weighting for a.
double powerHeuristic(const double a, const double b);

// Returns 1 if a > 0 and 0 otherwise
double positiveCharacteristic(const double a);

// Fast sampling algorithm taken from PBR Book using Gray codes.
double* SobolSample(const uint32_t* C, uint32_t n, uint32_t scramble, std::mt19937 gen);

// 2D Sobol sampling class, builds n samples on contruction and provides 
// them with next().
class Sobol {
    private:
        double* x;
        double* y;
        double min;
        double max;
        int i;
    public:
        Sobol(int n, double min, double max, std::mt19937 gen, std::uniform_int_distribution<uint32_t> dist);
        Vector2 next();
};

#endif