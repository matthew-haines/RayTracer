#include "vector3.hpp"
#include "naive_intersector.hpp"
#include "ray.hpp"
#include "primitive.hpp"
#include "constants.hpp"
#include <limits>
#include <vector>

NaiveIntersector::NaiveIntersector(std::vector<Primitive*> primitives): primitives(primitives) {};

double NaiveIntersector::getIntersect(Ray ray, Vector3 *intersect, Vector3 *normal, Primitive **primitive) {
    double closestDistance = std::numeric_limits<double>::max();
    Primitive* closestPrimitive;
    Vector3 tempIntersect, tempNormal;
    for (Primitive* primitive : primitives) {
        double distance = primitive->intersect(ray, &tempIntersect, &tempNormal);
        if (distance > -epsilon && distance < closestDistance) {
            *intersect = tempIntersect;
            *normal = tempNormal;
            closestDistance = distance;
            closestPrimitive = primitive;
        }
    }
    if (closestDistance == std::numeric_limits<double>::max()) {
        return -1;
    }
    else {
        *primitive = closestPrimitive;
        return closestDistance;
    }
}

bool NaiveIntersector::getShadowIntersect(Ray ray, double maxDistance) {
    // returns false if point light is blocked, else returns true
    Vector3 intersect, normal;
    for (Primitive* primitive : primitives) {
        double distance = primitive->intersect(ray, &intersect, &normal);
        if (distance != -1) {
            if (distance < maxDistance) return false;
        }
    }
    return true;
}
