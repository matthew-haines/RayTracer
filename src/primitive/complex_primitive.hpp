#ifndef COMPLEX_PRIMITIVE_HPP
#define COMPLEX_PRIMITIVE_HPP

#include "primitive.hpp"
#include <vector>

// Base struct for a logical group of primitives.
// Should probably be changed at some point.
struct ComplexPrimitive {
    std::vector<Primitive*> primitives;
};

#endif