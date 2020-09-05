#include "polygon.hpp"
#include "triangle.hpp"

Polygon::Polygon(std::vector<Vector3>& points, Material* const material) {
    for (int i = 1; i < points.size() - 1; i++) {
        primitives.push_back(new Triangle(points[0], points[i], points[i+1], material));
    }
}