#include "helpers.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

double sign(double x) {
    if (x > 0) {
        return 1;
    } else if (x == 0) {
        return 0;
    } else {
        return -1;
    }
}

char colorToChar(double color) {
    return (char)(std::min(color, 1.0) * 255);
}

// Samples hemisphere around (0, 0, 1)
Vector3 UniformSampleHemisphere::sample(double u1, double u2) {
    double z = u1;
    double r = std::sqrt(std::max(0., 1. - z * z));
    double phi = 2 * M_PI * u2;
    return Vector3(r * std::cos(phi), r * std::sin(phi), z);
}

double UniformSampleHemisphere::pdf(Vector3 v) {
    return 0.5 / M_PI;
}

Vector3 UniformSampleSphere::sample(double u1, double u2) {
    double alt = M_PI * u1;
    double azi = 2. * M_PI * u2 - M_PI;
    return sphericalToCartesian(Vector3(1.0, azi, alt));
}

double UniformSampleSphere::pdf() {
    return 0.25 / M_PI;
}

Vector3 UniformSampleCone::sample(double u1, double u2, Vector3 direction, double thetaMax) {
    double alt = thetaMax * u1;
    double azi = 2 * M_PI * u2;
    Vector3 result = sphericalToCartesian(Vector3(1., azi, alt));
    return Matrix3::createFromNormal(direction.normalized()) * result;
}

double UniformSampleCone::pdf(double cosThetaMax) {
    return 1 / (2 * M_PI * (1 - cosThetaMax));
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
    } else {
        r = u2;
        theta = M_PI_2 - M_PI_4 * (u1 / u2);
    }
    return r * Vector2(std::cos(theta), std::sin(theta));
}

double ConcentricSampleDisk::pdf(Vector2 v) {
    return 0.5 / M_PI;
}

// Samples hemisphere around (0, 0, 1)
Vector3 CosineSampleHemisphere::sample(double u1, double u2) {
    Vector2 diskMapping = ConcentricSampleDisk::sample(u1, u2);
    double z = std::sqrt(std::max(0., 1. - square(diskMapping.x) - square(diskMapping.y)));
    return Vector3(diskMapping.x, diskMapping.y, z);
}

double CosineSampleHemisphere::pdf(double cosTheta) {
    return (cosTheta / M_PI);
}

// Takes threads and function to apply at each iteration of loop, function takes index
void parallelizeLoop(int threads, std::function<void(int)> func, int range, bool showProgress) {
    std::vector<std::thread> threadpool;

    int blockSize = range / threads;

    int finished = 0;
    auto epoch = std::chrono::high_resolution_clock::now();
    std::function<void(int, int)> Process;
    if (showProgress) {
        Process = [func, &finished, range, epoch](int start, int stop) {
            for (int i = start; i < stop; ++i) {
                func(i);
                finished++;
                if (finished % (range / 100) == 0) {
                    auto now = std::chrono::high_resolution_clock::now();
                    double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - epoch).count();
                    int total = milliseconds / ((double)finished / (double)range);
                    std::cout << "\r" << 100 * finished / range << "\% (" << (int)(total - milliseconds) / 1000 << " s)     " << std::flush;
                }
            }
        };
    } else {
        Process = [func](int start, int stop) {
            for (int i = start; i < stop; ++i) {
                func(i);
            }
        };
    }

    for (int i = 0; i < threads; ++i) {
        threadpool.emplace_back(Process, i * blockSize, i == (threads-1) ? range : (i + 1) * blockSize);
    }

    for (auto& thread : threadpool) {
        thread.join();
    }
}

// Power heurstic weight for a
double powerHeuristic(double a, double b) {
    return square(a) / (square(a) + square(b));
}

// Returns 1 if a > 0 and 0 otherwise
double positiveCharacteristic(double a) {
    return a > 0 ? 1 : 0;
}