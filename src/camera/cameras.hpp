#ifndef CAMERAS_HPP
#define CAMERAS_HPP
#include "../vector3.hpp"
#include "../matrix3.hpp"
#include "../ray.hpp"
#include <vector>

std::vector<Ray> PerspectiveCamera(int width, int height, double fov, Vector3 direction);

#endif