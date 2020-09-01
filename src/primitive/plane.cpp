#include "plane.hpp"
#include "../constants.hpp"

Plane::Plane(Vector3 planeNormal, double d, Material *material, bool oneSided): Primitive(material), planeNormal(planeNormal), d(d),  oneSided(oneSided) {};

double Plane::intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
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

Vector3 Plane::sample(double u1, double u2) {
    // Not implemented
    return Vector3(0.);
}

double Plane::samplePdf(Vector3 point, Vector3 direction) {
    // Not implemented
    return 0.;
}

Vector3 Plane::directionalSample(double u1, double u2, Vector3 point) {
    // Not implemented
    return Vector3(0.);
}

double Plane::directionalSamplePdf(Vector3 point, Vector3 direction) {
    // Not implemented
    return 0.;
}

Bound Plane::getBound() {
    return Bound();
}