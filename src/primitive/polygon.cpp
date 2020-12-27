#include "polygon.hpp"
#include "material.hpp"
#include "triangle.hpp"

Polygon::Polygon(std::vector<Vector3>& points, const Material material) {
    for (int i = 1; i < points.size() - 1; i++) {
        primitives.push_back(new Triangle(points[0], points[i], points[i+1], material));
    }
}