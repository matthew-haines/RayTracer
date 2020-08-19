#include "perspective_camera.hpp"
#include <cmath>

PerspectiveCamera::PerspectiveCamera(double fov, std::size_t width, std::size_t height, Vector3 direction, Vector3 position): fov(fov), Camera(width, height, direction, position) {
    maxWidth = 2 * std::sqrt(1 / std::pow(std::cos(fov / 2), 2) - 1);
    gridSize = maxWidth / width;
    maxHeight = gridSize * height;
    
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(-gridSize / 2, gridSize / 2);
}

std::function<Ray()> PerspectiveCamera::PixelFunction(int row, int column) {
    auto func = [this, row, column]() {
        double jitter_y = dist(gen);
        double jitter_z = dist(gen);
        Vector3 rayDirection = rotation * Vector3(1.0, (maxWidth - gridSize) / 2 - column * gridSize + jitter_y, (maxHeight - gridSize) / 2 - row * gridSize + jitter_z).normalized();
        return Ray(position, direction);
    };
    return func;
}