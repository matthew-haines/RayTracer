#include "helpers.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include <cmath>

double sign(double x) {
    if (x > 0) {
        return 1;
    }
    else if (x == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

char ColorToChar(double color) {
    return (char)(std::min(color, 1.0) * 255);
}

Vector3 UniformSampleHemisphere::sample(double u1, double u2) {
    // Hemisphere around (0, 0, 1)
    double z = u1;
    double r = std::sqrt(std::max(0., 1. - z * z));
    double phi = 2 * M_PI * u2;
    return Vector3(r * std::cos(phi), r * std::sin(phi), z);
}

double UniformSampleHemisphere::pdf(Vector3 v) {
    return 0.5 / M_PI;
}

Vector2 ConcentricSampleDisk::sample(double u1, double u2) {
    // args are uniform on [0, 1]
    u1 = 2 * u1 - 1;
    u2 = 2 * u2 - 1;
    if (u1 == 0 && u2 == 0) {
        return Vector2(u1, u2);
    }

    double theta, r;
    if (std::abs(u1) > std::abs(u2)) {
        r = u1;
        theta = M_PI_4 * (u2 / u1);
    }
    else {
        r = u2;
        theta = M_PI_2 - M_PI_4 * (u1 / u2);
    }
    return r * Vector2(std::cos(theta), std::sin(theta));
}

double ConcentricSampleDisk::pdf(Vector2 v) {
    return 0.5 / M_PI;
}

Vector3 CosineSampleHemisphere::sample(double u1, double u2) {
    // Hemisphere around (0, 0, 1)
    Vector2 diskMapping = ConcentricSampleDisk::sample(u1, u2);
    double z = std::sqrt(std::max(0., 1. - square(diskMapping.x) - square(diskMapping.y)));
    return Vector3(diskMapping.x, diskMapping.y, z);
}
double CosineSampleHemisphere::pdf(double cosTheta) {
    return cosTheta / M_PI;
}