#include "pathtracer.hpp"
#include "../helpers.hpp"
#include <functional>
#include <thread>

PathTracer::PathTracer(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {};

std::vector<Vector3>& PathTracer::Render(std::vector<Ray>& rays, int threads) {
    std::vector<Vector3> image(rays.size());
    ParallelizeLoop(threads, std::function<void(int)>(std::bind(&PathTracer::Evaluate, this, std::placeholders::_1, rays, image)), rays.size());
}

void PathTracer::Evaluate(int index, std::vector<Ray>& rays, std::vector<Vector3>& image) {
    Intersection intersection;
    Vector3 color(0.);
    Ray& ray = rays[index];
    Ray& newRay;
    // needs to be changed to multiple importance sampling so that you can ignore emission in this term and solve iteratively without memo
    for (int depth = 0; depth < maxDepth; ++depth) {
        Vector3 tempColor(0.);
        if (!intersector->getIntersect(ray, intersection)) {
            tempColor = ambient;
            break;
        }
        else {
            newRay.origin = intersection.intersect + 0.001 * intersection.normal;
            double probability;
            Vector3 bxdf = intersection->primitive->material->bxdf->Evaluate(ray.direction, intersection.normal, newRay.direction, probability, true);
            color 
        }
    }
}