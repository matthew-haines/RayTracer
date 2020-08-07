#include "pathtracermis.hpp"
#include "../primitive/primitive.hpp"
#include "../helpers.hpp"
#include <functional>

PathTracerMIS::PathTracerMIS(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {
    std::random_device rd;
    gen = std::mt19937(rd);
    dist = std::uniform_real_distribution<double>(0, 1);
}

std::vector<Vector3> PathTracerMIS::Render(std::vector<Ray>& rays, int threads, int samples) {
    std::vector<Vector3> image(rays.size());
    ParallelizeLoop(threads, , rays.size());
    return image;
}

void PathTracerMIS::EvaluateWrapper(int index, std::vector<Ray>& rays, std::vector<Vector3>& image, int samples) {
    image[index] = Vector3(0.);
    for (int i = 0; i < samples; i++) {
        Vector3 result = Evaluate(rays[index], 1);
        image[index] += result;
    }
    image[index] /= (double)samples;
}

Vector3 PathTracerMIS::Evaluate(Ray ray, int depth) {
    // Combine estimate of direct lighting by sampling different lights in scene with an indirect ray with MIS (Veach '97 power heuristic)
    //direct
    Intersection intersection;
    if (!intersector.getIntersect(ray, intersection)) {
        return ambient;
    }
     
    // get random light
    Primitive& light = intersector.getRandomLight();
    // choose random point on light surface / get direction vector and evaluate probability of that ray
    double pointProbability;
    Vector3 point = light.DirectionalSample(dist(gen), dist(gen), pointProbability);
    // choose another direction based on bxdf
    // Weight probabilities with power heuristic
    // Sum with recursive call
}


