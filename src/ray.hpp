#ifndef RAY_HPP
#define RAY_HPP
#include "vector3.hpp"

typedef struct ray {
    const Vector3 origin, direction;
} Ray;

#endif