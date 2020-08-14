#ifndef COMPLEX_PRIMITIVE_HPP
#define COMPLEX_PRIMITIVE_HPP
#include "primitive.hpp"
#include <vector>

struct ComplexPrimitive {
    std::vector<Primitive*> primitives;
};

#endif