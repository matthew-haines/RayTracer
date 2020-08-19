#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP
#include "lighting_model.hpp"

class PathTracer: public LightingModel {
    public:
        PathTracer(Intersector& intersector, int maxDepth, Vector3 ambient=Vector3(0.));
    private:
        Vector3 Evaluate(Ray ray, int depth);
};

#endif