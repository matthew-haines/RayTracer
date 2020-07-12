#include "plane.hpp"
#include "../constants.hpp"

Plane::Plane(Vector3 planeNormal, double d, Material *material, bool polygon, std::vector<Vector3> *points, bool oneSided): Primitive(material), planeNormal(planeNormal), d(d), polygon(polygon), points(points), oneSided(oneSided) {};

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
    if (polygon) {
        
    }
    return t;
}