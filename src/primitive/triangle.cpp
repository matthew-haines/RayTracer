#include "triangle.hpp"
#include "constants.hpp"
#include "helpers.hpp"
#include "material.hpp"
#include <cmath>

Triangle::Triangle(const Vector3 v0, const Vector3 v1, const Vector3 v2, const Material material, const bool normals, const Vector3 vn0, const Vector3 vn1, const Vector3 vn2): Primitive(material), v0(v0), v1(v1), v2(v2), normals(normals), vn0(vn0), vn1(vn1), vn2(vn2) {
    e1 = (v1-v0);
    e2 = (v2-v0);
    planeNormal = e1.cross(e2).normalized();
    area = 0.5 * e1.cross(e2).length();
}

double Triangle::intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const {
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

Vector3 Triangle::sample(const double u1, const double u2) const {
    double sqrtu1 = std::sqrt(u1);
    return (1 - sqrtu1) * v0 + sqrtu1 * (1 - u2) * v1 + sqrtu1 * u2 * v2;
}

double Triangle::samplePdf(const Vector3 point, const Vector3 direction) const {
    return 1 / area;
}

Vector3 Triangle::directionalSample(const double u1, const double u2, const Vector3 point) const {
    return (sample(u1, u2) - point).normalized();
}

double Triangle::directionalSamplePdf(const Vector3 point, const Vector3 direction) const {
    Ray ray(point, direction);
    Vector3 intersection;
    Vector3 normal;
    if (intersect(ray, &intersection, &normal) != -1) {
        Vector3 distance = intersection - point;
        return distance.dot(distance) / (std::abs(normal.dot(-direction)) * area);
    } else {
        return 0;
    }
}

Bound Triangle::getBound() const {
    Vector3 min = Vector3::min(v0, Vector3::min(v1, v2));
    Vector3 max = Vector3::max(v0, Vector3::max(v1, v2));
    return Bound(min, max);
}

/* Possible implementation using barycentric coordinates, more of a pain to work with when making scenes.
Vector2 Triangle::getUVAtPoint(const Vector3& point) const {
    Vector3 p = point;
    double determinant = e1.dot(p);
    double invDeterminant = 1 / determinant;
    Vector3 origin = point - v0;
    double u = invDeterminant * origin.dot(p);// barycentric
    Vector3 q = origin.cross(e1);
    double v = point.dot(q) * invDeterminant;
    return Vector2(u, v); // this might work
}
*/

Vector2 Triangle::getUVAtPoint(const Vector3& point) const {
    // point = u * up + v * e1
    Vector3 up = planeNormal.cross(e1).normalized();
    up *= e1.length(); 
    Vector3 offset = point - v0;
    return Vector2(up.dot(offset), e1.dot(offset));
}