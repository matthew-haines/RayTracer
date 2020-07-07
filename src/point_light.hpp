#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP
#include "vector3.hpp"

typedef struct pointLight {
    Vector3 position;
    Vector3 color;
} PointLight;

#endif