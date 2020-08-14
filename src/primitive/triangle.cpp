#include "triangle.hpp"
#include "../constants.hpp"
#include "../ray.hpp"

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material): Primitive(material), v0(v0), v1(v1), v2(v2) {
    e1 = (v1-v0);
    e2 = (v2-v0);
    planeNormal = e1.cross(e2).normalized();
}

double Triangle::Intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
    // Muller Trombore
    Vector3 p = ray.direction.cross(e2);
    double determinant = e1.dot(p);
    if (std::abs(determinant) < epsilon) {
        return -1;
    }

    double invDeterminant = 1 / determinant;
    Vector3 origin = ray.origin - v0;
    double u = invDeterminant * origin.dot(p);// barycentric
    if (u < 0. || u > 1.) {
        // not allowed by barycentric
        return -1;
    }
    Vector3 q = origin.cross(e1);
    double v = ray.direction.dot(q) * invDeterminant;
    if (v < 0. || u+v > 1.) {
        // not allowed by barycentric
        return -1;
    }
    double distance = e2.dot(q) * invDeterminant;
    if (distance > epsilon) {
        *intersect = ray.origin + distance * ray.direction;
        *normal = determinant > 0. ? planeNormal : -planeNormal;
        return distance;
    }
    return -1;
}

Vector3 Triangle::Sample(double u1, double u2) {
    // Not implemented yet
    return Vector3(0.);
}

double Triangle::SamplePDF(Vector3 point, Vector3 direction) {
    // Not implemented yet
    return 0.;
}

Vector3 Triangle::DirectionalSample(double u1, double u2, Vector3 point) {
    // Not implemented yet
    return Vector3(0.);
}

double Triangle::DirectionalSamplePDF(Vector3 point, Vector3 direction) {
    // Not implemented yet
    return 0.;
}

Bound Triangle::GetBound() {
    Vector3 min = Vector3::min(v0, Vector3::min(v1, v2));
    Vector3 max = Vector3::max(v0, Vector3::max(v1, v2));
    return Bound(min, max);
}
