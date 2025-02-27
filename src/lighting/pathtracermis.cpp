#include "pathtracermis.hpp"
#include "primitive.hpp"
#include "helpers.hpp"
#include "constants.hpp"
#include <functional>
#include <iostream>

PathTracerMIS::PathTracerMIS(Intersector& intersector, const int maxDepth, const Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0, 1);
}

Vector3 PathTracerMIS::evaluate(const Ray ray, const int depth, const Intersection& lastIntersection) {
    // Combine estimate of direct lighting by sampling different lights in scene with an indirect ray with MIS (Veach '97 power heuristic)
    //direct
    if (depth > maxDepth) {
        return Vector3(0.);
    }

    Intersection intersection;
    if (!intersector.getIntersect(ray, intersection)) {
        return ambient;
    }

    Material material = intersection.primitive->material;
    Vector3 primitiveColor = intersection.primitive->color(intersection.intersect);

    if (material.emission != 0.) {
        if (depth == 1 || (lastIntersection.primitive != nullptr && lastIntersection.primitive->material.bxdf->specular)) {
            return primitiveColor * material.emission;
        } else {
            return Vector3(0.);
        }
    } else if (material.bxdf->specular) {
        Vector3 direction;
        double probability;
        Vector3 bxdfEval = (*material.bxdf)(ray.direction, intersection.normal, direction, probability);
        Vector3 result = evaluate({intersection.intersect, direction}, depth+1, intersection);
        return primitiveColor * bxdfEval * result / probability;
    } else {
        // get random light
        Primitive* light = intersector.getRandomLight();
        Vector3 misSampled = Vector3(0.);
        {
            Vector3 direction = light->directionalSample(dist(gen), dist(gen), intersection.intersect);
            double lightProbability = light->directionalSamplePdf(intersection.intersect, direction);
            if (lightProbability != 0.) {
                Vector3 bxdfEval = primitiveColor * material.bxdf->evaluate(ray.direction, intersection.normal, direction) * std::abs(intersection.normal.dot(direction));
                if (!(bxdfEval == Vector3(0.))) {
                    double bxdfProbability = material.bxdf->pdf(ray.direction, intersection.normal, direction);
                    Intersection lightIntersection;
                    if (intersector.getIntersect({intersection.intersect + epsilon * intersection.normal, direction}, lightIntersection)) {
                        if (lightIntersection.primitive == light) {
                            misSampled += light->color(lightIntersection.intersect) * light->material.emission * bxdfEval * powerHeuristic(lightProbability, bxdfProbability) / lightProbability;
                        }
                    }
                }
            }
        }
        Vector3 direction;
        double bxdfProbability;
        Vector3 bxdfEval;
        Vector3 nextRay = Vector3(0.);
        {
            bxdfEval = primitiveColor * (*material.bxdf)(ray.direction, intersection.normal, direction, bxdfProbability) * std::abs(intersection.normal.dot(direction));
            if (!(bxdfEval == Vector3(0.))) {
                double lightProbability = light->directionalSamplePdf(intersection.intersect, direction);
                Intersection lightIntersection;
                if (intersector.getIntersect({intersection.intersect + epsilon * intersection.normal, direction}, lightIntersection)) {
                    if (lightIntersection.primitive == light) {
                        misSampled += light->color(lightIntersection.intersect) * light->material.emission * bxdfEval * powerHeuristic(bxdfProbability, lightProbability) / bxdfProbability;
                    }
                }
                nextRay = evaluate({intersection.intersect + epsilon * intersection.normal, direction}, depth+1, intersection) * bxdfEval / bxdfProbability;
            }
        }
        return intersector.scene->lights.size() * misSampled + nextRay;
    }
}