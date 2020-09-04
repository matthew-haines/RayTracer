#include "polygon.hpp"

Polygon::Polygon(const Vector3 planeNormal, const double d, Material* const material, std::vector<Vector3>* const points, const bool oneSided): Plane(planeNormal, d, material, oneSided), points(points) {}

double Polygon::intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const {
    return 0.;
}