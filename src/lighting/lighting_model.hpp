#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP

#include "ray.hpp"
#include "intersector.hpp"
#include "camera.hpp"
#include <vector>

// Base class for any lighting integrator, handles most of the rendering.
class LightingModel {
    protected:
        Intersector& intersector;
        const int maxDepth;
        const Vector3 ambient;
    public:
        LightingModel(Intersector& intersector, const int maxDepth, const Vector3 ambient);
        void render(Camera& camera, const int threads, const int samples);
        // Recursive function defined by any derived class, evaluates the contribution of a given ray to the scene. 
        virtual Vector3 evaluate(const Ray ray, const int depth, const Intersection& lastIntersection)=0;
};

#endif