#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "camera.hpp"
#include <random>

class PerspectiveCamera: public Camera {
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<double> jitterDist;
        std::uniform_real_distribution<double> dofDist;
        std::uniform_int_distribution<uint32_t> uintdist;
        double gridSize;
        double maxWidth;
        double maxHeight;
        const bool jitter;
        const double focalDistance;
        const double lenseRadius;
    public:
        PerspectiveCamera(const double fov, const bool jitter, const double focalDistance, const double lenseRadius, const std::size_t width, const std::size_t height, const int samples, const Vector3 direction = Vector3(1, 0, 0), const Vector3 position = Vector3(0));
        std::function<Ray()> getPixelFunction(const int row, const int column);
};

#endif
