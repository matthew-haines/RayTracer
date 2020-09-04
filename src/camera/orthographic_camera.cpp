#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(const double scale, const bool jitter, const std::size_t width, const std::size_t height, Vector3 direction, Vector3 position): Camera(width, height, direction, position), jitter(jitter) {
    maxWidth = scale/2;
    gridSize = maxWidth / width;
    maxHeight = gridSize * height;
    
    if (jitter) {
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<double>(-gridSize / 2, gridSize / 2);
    }
    buildQueue();
}

std::function<Ray()> OrthographicCamera::getPixelFunction(const int row, const int column) {
    std::function<Ray()> func;
    if (jitter) {
        func = [this, row, column]() {
            double jitter_y = dist(gen);
            double jitter_z = dist(gen);
            Vector3 deltaposition = rotation * Vector3(0.0, (maxWidth - gridSize) / 2 - column * gridSize + jitter_y, (maxHeight - gridSize) / 2 - row * gridSize + jitter_z);
            return Ray((position + deltaposition).normalized(), direction);
        };
    } else {
        func = [this, row, column]() {
            Vector3 deltaPosition = rotation * Vector3(0, (maxWidth - gridSize) / 2 - column * gridSize, (maxHeight - gridSize) / 2 - row * gridSize);
            return Ray((position+deltaPosition).normalized(), direction);
        };
    }
    return func;
}