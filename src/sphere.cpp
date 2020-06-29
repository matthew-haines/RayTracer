#include "sphere.hpp"
#include "ray.hpp"
#include "math.h"
#include "constants.hpp"

Sphere::Sphere(Vector3 center, double radius): center(center), radius(radius) {
    radius2 = radius * radius;
}

double Sphere::intersect(Ray ray, Vector3 *intersectPoint, Vector3 *normal) {
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
    *intersectPoint = ray.direction * intersectDistance + ray.origin;
    *normal = (*intersectPoint - center) / radius;
    return intersectDistance;
};