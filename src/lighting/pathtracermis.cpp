#include "pathtracermis.hpp"
#include "../primitive/primitive.hpp"
#include "../helpers.hpp"
#include "../constants.hpp"
#include <functional>
#include <iostream>

PathTracerMIS::PathTracerMIS(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0, 1);
}

Vector3 PathTracerMIS::Evaluate(Ray ray, int depth) {
    // Combine estimate of direct lighting by sampling different lights in scene with an indirect ray with MIS (Veach '97 power heuristic)
    //direct
    if (depth > maxDepth) {
        return Vector3(0.);
    }

    Intersection intersection;
    if (!intersector.getIntersect(ray, intersection)) {
        return ambient;
    }

    Material* material = intersection.primitive->material;

    if (material->emission != 0.) {
        if (depth == 1) {
            return material->color * material->emission;
        } else {
            return Vector3(0.);
        }
    } else if (material->bxdf->specular) {
        Vector3 direction = material->bxdf->Sample(ray.direction, intersection.normal);
        return material->bxdf->Evaluate(ray.direction, intersection.normal, direction) * Evaluate({intersection.intersect, direction}, depth+1);
    } else {
        // get random light
        Primitive* light = intersector.getRandomLight();
        // choose random point on light surface / get direction vector and evaluate probability of that ray
        Vector3 misSampled = Vector3(0.);
        {
            Vector3 direction = light->DirectionalSample(dist(gen), dist(gen), intersection.intersect);
            double lightProbability = light->DirectionalSamplePDF(intersection.intersect, direction);
            if (lightProbability != 0.) {
                Vector3 bxdfEval = material->color * material->bxdf->Evaluate(ray.direction, intersection.normal, direction) * intersection.normal.dot(direction);
                double bxdfProbability = material->bxdf->pdf(ray.direction, intersection.normal, direction);
                Intersection lightIntersection;
                if (intersector.getIntersect({intersection.intersect, direction}, lightIntersection)) {
                    if (lightIntersection.primitive == light) {
                        misSampled += light->material->color * light->material->emission * bxdfEval * PowerHeuristic(lightProbability, bxdfProbability) / lightProbability;
                    }
                }
            }
        }
        Vector3 direction;
        double bxdfProbability;
        Vector3 bxdfEval;
        {
            direction = material->bxdf->Sample(ray.direction, intersection.normal);
            bxdfProbability = material->bxdf->pdf(ray.direction, intersection.normal, direction);
            bxdfEval = material->color * material->bxdf->Evaluate(ray.direction, intersection.normal, direction) * intersection.normal.dot(direction);
            double lightProbability = light->DirectionalSamplePDF(intersection.intersect, direction);
            Intersection lightIntersection;
            if (intersector.getIntersect({intersection.intersect, direction}, lightIntersection)) {
                if (lightIntersection.primitive == light) {
                    misSampled += light->material->color * light->material->emission * bxdfEval * PowerHeuristic(bxdfProbability, lightProbability) / bxdfProbability;
                }
            }
        }

        Vector3 nextRay = Evaluate({intersection.intersect, direction}, depth+1) * bxdfEval / bxdfProbability;
        return intersector.scene->lights.size() * misSampled + nextRay;
    }
}