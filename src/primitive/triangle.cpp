#include "triangle.hpp"
#include "../constants.hpp"
#include "../ray.hpp"
#include "../helpers.hpp"
#include <cmath>

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material, bool normals, Vector3 vn0, Vector3 vn1, Vector3 vn2): Primitive(material), v0(v0), v1(v1), v2(v2), normals(normals), vn0(vn0), vn1(vn1), vn2(vn2) {
    e1 = (v1-v0);
    e2 = (v2-v0);
    planeNormal = e1.cross(e2).normalized();
    area = 0.5 * e1.cross(e2).length();
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
        if (normals) {
            *normal = u * vn0 + v * vn1 + (1. - u - v) * vn2;
        } else {
            *normal = planeNormal;
        }
        *normal = determinant > 0. ? *normal : -*normal;
        return distance;
    }
    return -1;
}

Vector3 Triangle::Sample(double u1, double u2) {
    double sqrtu1 = std::sqrt(u1);
    return (1 - sqrtu1) * v0 + sqrtu1 * (1 - u2) * v1 + sqrtu1 * u2 * v2;
}

double Triangle::SamplePDF(Vector3 point, Vector3 direction) {
    return 1 / area;
}

Vector3 Triangle::DirectionalSample(double u1, double u2, Vector3 point) {
    return (Sample(u1, u2) - point).normalized();
}

double Triangle::DirectionalSamplePDF(Vector3 point, Vector3 direction) {
    Ray ray(point, direction);
    Vector3 intersect;
    Vector3 normal;
    if (Intersect(ray, &intersect, &normal) != -1) {
        Vector3 distance = intersect - point;
        return distance.dot(distance) / (std::abs(normal.dot(-direction)) * area);
    } else {
        return 0;
    }
}

Bound Triangle::GetBound() {
    Vector3 min = Vector3::min(v0, Vector3::min(v1, v2));
    Vector3 max = Vector3::max(v0, Vector3::max(v1, v2));
    return Bound(min, max);
}
