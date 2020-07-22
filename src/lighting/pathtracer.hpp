#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP
#include "lighting_model.hpp"

class PathTracer: public LightingModel {
    public:
        PathTracer(Intersector& intersector, int maxDepth, Vector3 ambient=Vector3(0., 0., 0.));
        std::vector<Vector3>& Render(std::vector<Ray> &rays, int threads);
        void Evaluate(int index);
};

#endif