#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "primitive/primitive.hpp"

typedef struct intersection {
    Vector3 intersect;
    Vector3 normal;
    Primitive* primitive;
    double distance;
} Intersection;

#endif
