#include "polygon.hpp"

Polygon::Polygon(Vector3 planeNormal, double d, Material *material, std::vector<Vector3> *points, bool oneSided): Plane(planeNormal, d, material, oneSided), points(points) {}

double Polygon::intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
    return 0.;
}