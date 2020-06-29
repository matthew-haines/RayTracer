#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP
#include "vector3.hpp"
#include "color.hpp"

typedef struct pointLight {
    Vector3 position;
    Color color;
} PointLight;

#endif