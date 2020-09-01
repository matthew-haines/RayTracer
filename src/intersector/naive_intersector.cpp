#include "naive_intersector.hpp"
#include "../constants.hpp"
#include <limits>

NaiveIntersector::NaiveIntersector(Scene* scene): Intersector(scene) {};

bool NaiveIntersector::getIntersect(Ray ray, Intersection& intersection) {
    double closestDistance = std::numeric_limits<double>::max();
    Primitive* closestPrimitive;
    Vector3 tempIntersect, tempNormal;
    for (Primitive* primitive : scene->primitives) {
        double distance = primitive->intersect(ray, &tempIntersect, &tempNormal);
        if (distance > -epsilon && distance < closestDistance) {
            intersection.intersect = tempIntersect;
            intersection.normal = tempNormal;
            closestDistance = distance;
            closestPrimitive = primitive;
        }
    }
    if (closestDistance == std::numeric_limits<double>::max()) {
        return false;
    } else {
        intersection.distance = closestDistance;
        intersection.primitive = closestPrimitive;
        return true;
    }
}
