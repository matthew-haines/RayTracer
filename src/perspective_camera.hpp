#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP
#include "camera.hpp"
#include "ray.hpp"
#include "surface.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include <functional>

class PerspectiveCamera: Camera {
    private:
        Ray** rays;
        Color** colors;
    public:
        int width, height;
        PerspectiveCamera(int width, int height, double fov, Vector3 direction);
        void generate(std::function<Color(Ray, int, Surface)> raytrace, Surface medium);
        void write(char* filename);
};

#endif