#include "pathtracermis.hpp"
#include "../primitive/primitive.hpp"
#include "../helpers.hpp"
#include <functional>

PathTracerMIS::PathTracerMIS(Intersector& intersector, int maxDepth, Vector3 ambient): LightingModel(intersector, maxDepth, ambient) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0, 1);
}

std::vector<Vector3> PathTracerMIS::Render(std::vector<Ray>& rays, int threads, int samples) {
    std::vector<Vector3> image(rays.size());
    ParallelizeLoop(threads, std::bind(&PathTracerMIS::EvaluateWrapper, this, std::placeholders::_1, std::ref(rays), std::ref(image), samples), rays.size());
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
        Vector3 lightDirection = light->DirectionalSample(dist(gen), dist(gen), intersection.intersect);
        double lightProbability = light->DirectionalSamplePDF(intersection.intersect, lightDirection);
        Vector3 lightColor;
        if (lightProbability != 0.) {
            Vector3 lightSampleBxDF = material->bxdf->Evaluate(ray.direction, intersection.normal, lightDirection);
            lightProbability *= material->bxdf->pdf(ray.direction, intersection.normal, lightDirection);
            Intersection lightIntersection;
            if (intersector.getIntersect({intersection.intersect, lightDirection}, lightIntersection)) {
                if (lightIntersection.primitive != light) {
                    lightColor = Vector3(0.);
                } else {
                    lightColor = lightIntersection.primitive->material->color * lightSampleBxDF * lightIntersection.primitive->material->emission * intersection.normal.dot(lightDirection);
                }
            }
        }

        // choose another direction based on bxdf (another solid angle)
        Vector3 BxDFDirection = material->bxdf->Sample(ray.direction, intersection.normal);
        double BxDFProbability = material->bxdf->pdf(ray.direction, intersection.normal, BxDFDirection);
        double totalBxDFProbability = BxDFProbability * light->DirectionalSamplePDF(intersection.intersect, BxDFDirection);
        Vector3 BxDFColor(0.);
        if (BxDFProbability != 0.)  {
            Intersection lightIntersection;
            Vector3 lightSampleBxDF = material->bxdf->Evaluate(ray.direction, intersection.normal, BxDFDirection);
            if (intersector.getIntersect({intersection.intersect, BxDFDirection}, lightIntersection)) {
                if (lightIntersection.primitive != light) {
                    BxDFColor = Vector3(0.);
                } else {
                    BxDFColor = lightIntersection.primitive->material->color * lightSampleBxDF * lightIntersection.primitive->material->emission * intersection.normal.dot(BxDFDirection);
                }
            }
        }
        // Weight probabilities with power heuristic
        return material->color * (intersector.scene->lights.size() * (lightColor * PowerHeuristic(lightProbability, totalBxDFProbability) + BxDFColor * PowerHeuristic(totalBxDFProbability, lightProbability)) + BxDFColor * Evaluate({intersection.intersect, BxDFDirection}, depth+1) / BxDFProbability * intersection.normal.dot(BxDFDirection));
    }
}


