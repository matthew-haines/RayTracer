#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"

struct Ray {
    Vector3 origin, direction;
    Ray()=default;
    Ray(Vector3 origin, Vector3 direction): origin(origin), direction(direction) {};
};

#endif