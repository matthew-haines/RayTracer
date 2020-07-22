#include "importance_sampling_model.hpp"
#include "../intersection.hpp"

ImportanceSamplingModel::ImportanceSamplingModel(Vector3 ambient, Intersector *intersector, int maxDepth): LightingModel(ambient, intersector, maxDepth) {}

Vector3 ImportanceSamplingModel::Evaluate(Ray ray, int depth) {
    Intersection intersection;
    if(!intersector->getIntersect(ray, intersection)) {
        return ambient;
    }
    Vector3 color(0., 0., 0.);
    if (depth < maxDepth) {
        Ray newRay;
        newRay.origin = intersect + 0.001 * normal;
        double probability;
        Vector3 bxdf = primitive->material->bxdf->Evaluate(ray.direction, normal, newRay.direction, probability, true);
        color += primitive->material->color * bxdf * Evaluate(newRay, depth+1) / probability * normal.dot(newRay.direction);
    }
    color += primitive->material->emission;
    return color;
}