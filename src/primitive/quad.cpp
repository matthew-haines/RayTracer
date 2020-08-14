#include "quad.hpp"
#include "triangle.hpp"

Quad::Quad(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Material *material) {
    primitives.push_back(new Triangle(v0, v1, v2, material));
    primitives.push_back(new Triangle(v0, v2, v3, material));
}