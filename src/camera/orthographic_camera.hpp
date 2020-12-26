#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "camera.hpp"
#include <random>

class OrthographicCamera: public Camera {
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;
        double gridSize;
        double maxWidth;
        double maxHeight;
        const bool jitter;
    public:
        OrthographicCamera(const double scale, const bool jitter, const std::size_t width, const std::size_t height, const int samples, const Vector3 direction = Vector3(1, 0, 0), const Vector3 position = Vector3(0));
        std::function<Ray()> getPixelFunction(const int row, const int column);
};

#endif

