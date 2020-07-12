#include "uniform_sampling_model.hpp"

UniformSamplingModel::UniformSamplingModel(Vector3 ambient, Intersector *intersector, int maxDepth): LightingModel(ambient, intersector, maxDepth) {}

Vector3 UniformSamplingModel::Evaluate(Ray ray, int depth) {
    Vector3 intersect, normal;
    Primitive *primitive;
    double distance = intersector->getIntersect(ray, &intersect, &normal, &primitive);
    if (distance == -1) {
        return ambient;
    }
    Vector3 color(0., 0., 0.);
    if (depth < maxDepth) {
        Ray newRay;
        newRay.origin = intersect + 0.001 * normal;
        double probability;
        Vector3 bxdf = primitive->material->bxdf->Evaluate(ray.direction, normal, newRay.direction, probability, false);
        color += primitive->material->color * bxdf * Evaluate(newRay, depth+1) / probability * normal.dot(newRay.direction);
    }
    color += primitive->material->emission;
    return color;
}