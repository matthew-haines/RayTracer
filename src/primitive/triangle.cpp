#include "triangle.hpp"
#include "../ray.hpp"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material): v0(v0), v1(v1), v2(v2), Primitive(material) {

}

double Triangle::intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {

}