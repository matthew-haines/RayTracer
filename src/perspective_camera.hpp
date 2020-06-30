#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP
#include <functional>
#include "camera.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "vector3.hpp"

class PerspectiveCamera: Camera {
    private:
        Ray** rays;
        Color** colors;
    public:
        int width, height;
        PerspectiveCamera(int width, int height, double fov, Vector3 direction);
        void generate(std::function<Color(Ray, int)> raytrace);
        void write(char*);
};

#endif