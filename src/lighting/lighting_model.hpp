#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP

#include "../ray.hpp"
#include "../intersector/intersector.hpp"
#include "../camera/camera.hpp"
#include <vector>

class LightingModel {
    protected:
        Intersector& intersector;
        const int maxDepth;
        Vector3 ambient;
    public:
        LightingModel(Intersector& intersector, int maxDepth, Vector3 ambient);
        void render(Camera& camera, int threads, int samples);
        virtual Vector3 evaluate(Ray ray, int depth, Intersection& lastIntersection)=0;
};

#endif