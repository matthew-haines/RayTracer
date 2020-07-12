#include "triangle.hpp"
#include "../ray.hpp"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material): Primitive(material), v0(v0), v1(v1), v2(v2) {}

double Triangle::intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
    return 0.0;
}