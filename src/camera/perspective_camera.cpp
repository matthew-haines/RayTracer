#include "perspective_camera.hpp"
#include "../helpers.hpp"
#include <cmath>

PerspectiveCamera::PerspectiveCamera(const double fov, const bool jitter, const double focalDistance, const double lenseRadius, const std::size_t width, const std::size_t height, const Vector3 direction, const Vector3 position): Camera(width, height, direction, position), jitter(jitter), focalDistance(focalDistance), lenseRadius(lenseRadius) {
    maxWidth = 2 * std::tan(fov / 2) * focalDistance;
    gridSize = maxWidth / width;
    maxHeight = gridSize * height;

    std::random_device rd;
    gen = std::mt19937(rd());

    if (lenseRadius != 0.) {
        dofDist = std::uniform_real_distribution<double>(0, 1);
    }

    if (jitter) {
        jitterDist = std::uniform_real_distribution<double>(-gridSize / 2, gridSize / 2);
    }

    buildQueue();
}

std::function<Ray()> PerspectiveCamera::getPixelFunction(const int row, const int column) {
    std::function<Ray()> func;
    if (lenseRadius != 0.) {
        func = [this, row, column]() {
            double jitter_y = jitterDist(gen);
            double jitter_z = jitterDist(gen);
            Vector3 normalPoint = rotation * Vector3(focalDistance, (maxWidth - gridSize) / 2 - column * gridSize + jitter_y, (maxHeight - gridSize) / 2 - row * gridSize + jitter_z);
            Vector2 point = lenseRadius * ConcentricSampleDisk::sample(dofDist(gen), dofDist(gen));
            Vector3 origin = rotation * Vector3(0, point.x, point.y);
            Vector3 direction = normalPoint - origin;
            return Ray(origin + position, direction.normalized() + position);
        };
    } else if (jitter) {
        func = [this, row, column]() {
            double jitter_y = jitterDist(gen);
            double jitter_z = jitterDist(gen);
            Vector3 rayDirection = rotation * Vector3(1.0, (maxWidth - gridSize) / 2 - column * gridSize + jitter_y, (maxHeight - gridSize) / 2 - row * gridSize + jitter_z).normalized();
            return Ray(position, rayDirection);
        };
    } else {
        func = [this, row, column]() {
            Vector3 rayDirection = rotation * Vector3(1.0, (maxWidth - gridSize) / 2 - column * gridSize, (maxHeight - gridSize) / 2 - row * gridSize).normalized();
            return Ray(position, rayDirection);
        };
    }
    return func;
}