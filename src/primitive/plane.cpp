#include "plane.hpp"
#include "../constants.hpp"

Plane::Plane(Vector3 planeNormal, double d, Material *material, bool oneSided): Primitive(material), planeNormal(planeNormal), d(d),  oneSided(oneSided) {};

double Plane::Intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
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

Vector3 Plane::Sample(double u1, double u2) {
    // Not implemented
    return Vector3(0.);
}

double Plane::SamplePDF(Vector3 point, Vector3 direction) {
    // Not implemented
    return 0.;
}

Vector3 Plane::DirectionalSample(double u1, double u2, Vector3 point) {
    // Not implemented
    return Vector3(0.);
}

double Plane::DirectionalSamplePDF(Vector3 point, Vector3 direction) {
    // Not implemented
    return 0.;
}

Bound Plane::GetBound() {
    return Bound();
}