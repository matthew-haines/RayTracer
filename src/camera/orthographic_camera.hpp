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
        bool jitter;
    public:
        double scale;
        OrthographicCamera(double scale, bool jitter, std::size_t width, std::size_t height, Vector3 direction = Vector3(1, 0, 0), Vector3 position = Vector3(0));
        virtual std::function<Ray()> PixelFunction(int row, int column);
};

#endif

