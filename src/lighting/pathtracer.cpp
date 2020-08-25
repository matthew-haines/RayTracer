#include "pathtracer.hpp"
#include "../helpers.hpp"
#include <functional>

PathTracer::PathTracer(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {}

Vector3 PathTracer::Evaluate(Ray ray, int depth, Intersection& lastIntersection) {
    Intersection intersection;
    if (!intersector.getIntersect(ray, intersection)) {
        return ambient;
    }
    Vector3 color(0.);
    if (depth < maxDepth) {
        Ray newRay;
        newRay.origin = intersection.intersect + 0.0001 * intersection.normal;
        Material* material = intersection.primitive->material;
        double probability;
        Vector3 bxdf = material->bxdf->operator()(ray.direction, intersection.normal, newRay.direction, probability);
        color += material->color * bxdf * Evaluate(newRay, depth+1, intersection) / probability * intersection.normal.dot(newRay.direction);
    }
    color += intersection.primitive->material->emission;
    return color;
}