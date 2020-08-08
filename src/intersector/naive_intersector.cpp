#include "../vector3.hpp"
#include "naive_intersector.hpp"
#include "../ray.hpp"
#include "../primitive/primitive.hpp"
#include "../constants.hpp"
#include <limits>
#include <vector>

NaiveIntersector::NaiveIntersector(Scene* scene): scene(scene) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<int>(0, scene->lights.size()-1);
};

bool NaiveIntersector::getIntersect(Ray ray, Intersection& intersection) {
    double closestDistance = std::numeric_limits<double>::max();
    Primitive* closestPrimitive;
    Vector3 tempIntersect, tempNormal;
    for (Primitive* primitive : scene->primitives) {
        double distance = primitive->Intersect(ray, &tempIntersect, &tempNormal);
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

Primitive* NaiveIntersector::getRandomLight() {
    return &(*scene->lights[dist(gen)]);
}