#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>

#include "complex_primitive.hpp"

struct Polygon: public ComplexPrimitive {
    Polygon(std::vector<Vector3>& points, Material* const material);
};

#endif