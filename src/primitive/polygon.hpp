#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>

#include "complex_primitive.hpp"
#include "material.hpp"

// Polygon, builds a series of triangles that represent a polygon
// made from a list of points.
struct Polygon: public ComplexPrimitive {
    Polygon(std::vector<Vector3>& points, const Material material);
};

#endif