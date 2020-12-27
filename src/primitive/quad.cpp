#include "quad.hpp"
#include "triangle.hpp"

Quad::Quad(const Vector3 v0, const Vector3 v1, const Vector3 v2, const Vector3 v3, const Material material) {
    primitives.push_back(new Triangle(v0, v1, v2, material));
    primitives.push_back(new Triangle(v0, v2, v3, material));
}