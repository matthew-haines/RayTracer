#ifndef QUAD_HPP
#define QUAD_HPP

#include "complex_primitive.hpp"

struct Quad: public ComplexPrimitive {
    Quad(const Vector3 v0, const Vector3 v1, const Vector3 v2, const Vector3 v3, Material* const material);
};

#endif