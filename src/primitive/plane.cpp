#include "plane.hpp"
#include "constants.hpp"
#include "material.hpp"

Plane::Plane(const Vector3 planeNormal, const double d, const Material material, const bool oneSided): Primitive(material), planeNormal(planeNormal), d(d),  oneSided(oneSided) {};

double Plane::intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const {
   double vd = planeNormal.dot(ray.direction);
    if (vd > 0.0 && (oneSided || vd < epsilon)) {
        return -1;
    }
    double v0 = -(planeNormal.dot(ray.origin) + d);
    double t = v0 / vd;
    if (t < -epsilon) {
        return -1;
    }
    *intersect = t * ray.direction + ray.origin;
    *normal = vd ? planeNormal : -planeNormal;
    return t;
}

Vector3 Plane::sample(const double u1, const double u2) const {
    // Not implemented
    return Vector3(0.);
}

double Plane::samplePdf(const Vector3 point, const Vector3 direction) const {
    // Not implemented
    return 0.;
}

Vector3 Plane::directionalSample(const double u1, const double u2, const Vector3 point) const {
    // Not implemented
    return Vector3(0.);
}

double Plane::directionalSamplePdf(const Vector3 point, const Vector3 direction) const {
    // Not implemented
    return 0.;
}

Bound Plane::getBound() const {
    // Not implemented
    return Bound();
}

Vector2 Plane::getUVAtPoint(const Vector3& point) const {
    // Not implemented
    return Vector2();
}