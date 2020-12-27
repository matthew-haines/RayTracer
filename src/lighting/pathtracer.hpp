#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include "lighting_model.hpp"

// Naive path tracer, includes simple importance sampling.
class PathTracer: public LightingModel {
    public:
        PathTracer(Intersector& intersector, const int maxDepth, const Vector3 ambient=Vector3(0.));
    private:
        Vector3 evaluate(const Ray ray, const int depth, const Intersection& lastIntersection);
};

#endif