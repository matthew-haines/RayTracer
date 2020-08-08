#include "pathtracer.hpp"
#include "../helpers.hpp"
#include <functional>

PathTracer::PathTracer(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {}

std::vector<Vector3> PathTracer::Render(std::vector<Ray>& rays, int threads, int samples) {
    std::vector<Vector3> image(rays.size());
    ParallelizeLoop(threads, std::bind(&PathTracer::EvaluateWrapper, this, std::placeholders::_1, std::ref(rays), std::ref(image), samples), rays.size());
    return image;
}

void PathTracer::EvaluateWrapper(int index, std::vector<Ray>& rays, std::vector<Vector3>& image, int samples) {
    image[index] = Vector3(0.);
    for (int i = 0; i < samples; i++) {
        Vector3 result = Evaluate(rays[index], 1);
        image[index] += result;
    }
    image[index] /= (double)samples;
}

Vector3 PathTracer::Evaluate(Ray ray, int depth) {
    Intersection intersection;
    if (!intersector.getIntersect(ray, intersection)) {
        return ambient;
    }
    Vector3 color(0.);
    if (depth < maxDepth) {
        Ray newRay = {};
        newRay.origin = intersection.intersect + 0.0001 * intersection.normal;
        Material* material = intersection.primitive->material;
        newRay.direction = material->bxdf->Sample(ray.direction, intersection.normal);
        Vector3 bxdf = material->bxdf->Evaluate(ray.direction, intersection.normal, newRay.direction);
        double probability = material->bxdf->pdf(ray.direction, intersection.normal, newRay.direction);
        color += material->color * bxdf * Evaluate(newRay, depth+1) / probability * intersection.normal.dot(newRay.direction);
    }
    color += intersection.primitive->material->emission;
    return color;
}