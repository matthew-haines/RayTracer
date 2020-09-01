#ifndef QUAD_HPP
#define QUAD_HPP

#include "complex_primitive.hpp"

struct Quad: ComplexPrimitive {
    Quad(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Material *material);
};

#endif