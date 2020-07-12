#ifndef HELPERS_HPP
#define HELPERS_HPP
#include "vector2.hpp"
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

namespace sampling {
    struct UniformSampleHemisphere {
        static Vector3 sample(double u1, double u2) {
            // Hemisphere around (0, 0, 1)
            double z = u1;
            double r = std::sqrt(std::max(0., 1. - z * z));
            double phi = 2 * M_PI * u2;
            return Vector3(r * std::cos(phi), r * std::sin(phi), z);
        }
        static double pdf(Vector3 v) {
            return 0.5 / M_PI;
        }
    };

    struct ConcentricSampleDisk {
        static Vector2 sample(double u1, double u2) {
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
        static double pdf(Vector2 v) {
            return 0.5 / M_PI;
        }
    };
    
    struct CosineSampleHemisphere {
        static Vector3 sample(double u1, double u2) {
            // Hemisphere around (0, 0, 1)
            Vector2 diskMapping = ConcentricSampleDisk::sample(u1, u2);
            double z = std::sqrt(std::max(0., 1. - square(diskMapping.x) - square(diskMapping.y)));
            return Vector3(diskMapping.x, diskMapping.y, z);
        }
        static double pdf(double cosTheta) {
            return cosTheta / M_PI;
        }
    };
}

#endif