#include "sphere.hpp"
#include "../constants.hpp"
#include <math.h>

Sphere::Sphere(Vector3 center, double radius, Material *material): Primitive(material), center(center), radius(radius) {
    radius2 = radius * radius;
}

double Sphere::intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
    Vector3 distance = center - ray.origin;
    double distance2 = distance.dot(distance);
    double lengthToClosest = distance.dot(ray.direction);
    if (lengthToClosest < -epsilon) {
        return -1;
    }
    double halfChordDistance2 = radius2 - distance2 + lengthToClosest * lengthToClosest;
    if (halfChordDistance2 < -epsilon) {
        return -1;
    }
    double intersectDistance;
    if (distance2 > radius2) {
        // Ray outside sphere
        intersectDistance = lengthToClosest - sqrt(halfChordDistance2);
    }
    else {
        // Ray inside sphere
        intersectDistance = lengthToClosest + sqrt(halfChordDistance2);
    }
    *intersect = ray.direction * intersectDistance + ray.origin;
    *normal = (*intersect - center) / radius;
    return intersectDistance;
};