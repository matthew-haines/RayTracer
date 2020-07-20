#ifndef COMPLEX_PRIMITIVE_HPP
#define COMPLEX_PRIMITIVE_HPP
#include "primitive.hpp"
#include <vector>

typedef struct complexPrimitive {
    std::vector<Primitive*> primitives;
} ComplexPrimitive;

#endif