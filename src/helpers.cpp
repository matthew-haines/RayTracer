#include "helpers.hpp"
#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

double sign(const double x) {
    if (x > 0) {
        return 1;
    } else if (x == 0) {
        return 0;
    } else {
        return -1;
    }
}

char colorToChar(const double color) {
    return (char)(std::min(color, 1.0) * 255);
}

double charToColor(const unsigned char color) {
    return (double)color / 255.0;
}

Vector3 UniformSampleHemisphere::sample(const double u1, const double u2) {
    double z = u1;
    double r = std::sqrt(std::max(0., 1. - z * z));
    double phi = 2 * M_PI * u2;
    return Vector3(r * std::cos(phi), r * std::sin(phi), z);
}

double UniformSampleHemisphere::pdf(const Vector3 v) {
    return 0.5 / M_PI;
}

Vector3 UniformSampleSphere::sample(const double u1, const double u2) {
    double alt = M_PI * u1;
    double azi = 2. * M_PI * u2 - M_PI;
    return sphericalToCartesian(Vector3(1.0, azi, alt));
}

double UniformSampleSphere::pdf() {
    return 0.25 / M_PI;
}

Vector3 UniformSampleCone::sample(const double u1, const double u2, const Vector3 direction, const double thetaMax) {
    double alt = thetaMax * u1;
    double azi = 2 * M_PI * u2;
    Vector3 result = sphericalToCartesian(Vector3(1., azi, alt));
    return Matrix3::createFromNormal(direction.normalized()) * result;
}

double UniformSampleCone::pdf(const double cosThetaMax) {
    return 1 / (2 * M_PI * (1 - cosThetaMax));
}
 
Vector2 ConcentricSampleDisk::sample(double u1, double u2) {
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

double ConcentricSampleDisk::pdf() {
    return 0.5 / M_PI;
}

Vector3 CosineSampleHemisphere::sample(const double u1, const double u2) {
    Vector2 diskMapping = ConcentricSampleDisk::sample(u1, u2);
    double z = std::sqrt(std::max(0., 1. - square(diskMapping.x) - square(diskMapping.y)));
    return Vector3(diskMapping.x, diskMapping.y, z);
}

double CosineSampleHemisphere::pdf(const double cosTheta) {
    return (cosTheta / M_PI);
}

void parallelizeLoop(const int threads, const std::function<void(int)> func, const int range, const bool showProgress) {
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

double powerHeuristic(const double a, const double b) {
    return square(a) / (square(a) + square(b));
}

double positiveCharacteristic(const double a) {
    return a > 0 ? 1 : 0;
}

std::vector<double> SobolSample(const uint32_t* C, uint32_t n, uint32_t scramble, std::mt19937 gen) {
    uint32_t v = scramble; 
    std::vector<double> out(n);
    for (uint32_t i = 0; i < n; ++i) {
        out[i] = std::min((double)(v * 0x1p-32f), 1.);
        v ^= C[__builtin_ctz(i+1)]; // __builtin_ctz: count trailing zeros
    }
    std::shuffle(out.begin(), out.end(), gen);
    return out;
}

Sobol::Sobol(int n, double min, double max, std::mt19937 gen, std::uniform_int_distribution<uint32_t> dist): min(min), max(max) {
    // 2D Sampling Matrix taken from PBR Book
    const uint32_t CSobol[2][32] = {
        {0x80000000, 0x40000000, 0x20000000, 0x10000000, 0x8000000, 0x4000000,
         0x2000000, 0x1000000, 0x800000, 0x400000, 0x200000, 0x100000, 0x80000,
         0x40000, 0x20000, 0x10000, 0x8000, 0x4000, 0x2000, 0x1000, 0x800,
         0x400, 0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1},
        {0x80000000, 0xc0000000, 0xa0000000, 0xf0000000, 0x88000000, 0xcc000000,
         0xaa000000, 0xff000000, 0x80800000, 0xc0c00000, 0xa0a00000, 0xf0f00000,
         0x88880000, 0xcccc0000, 0xaaaa0000, 0xffff0000, 0x80008000, 0xc000c000,
         0xa000a000, 0xf000f000, 0x88008800, 0xcc00cc00, 0xaa00aa00, 0xff00ff00,
         0x80808080, 0xc0c0c0c0, 0xa0a0a0a0, 0xf0f0f0f0, 0x88888888, 0xcccccccc,
         0xaaaaaaaa, 0xffffffff}}; 
    x = SobolSample(CSobol[0], n, dist(gen), gen);
    y = SobolSample(CSobol[1], n, dist(gen), gen);
    i = 0; 
}

Vector2 Sobol::next() {
    Vector2 r(x[i], y[i]);
    i++;
    return (r * (max - min)) + min;
}
