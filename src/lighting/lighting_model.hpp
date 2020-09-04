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
        const Vector3 ambient;
    public:
        LightingModel(Intersector& intersector, const int maxDepth, const Vector3 ambient);
        void render(Camera& camera, const int threads, const int samples);
        virtual Vector3 evaluate(const Ray ray, const int depth, const Intersection& lastIntersection)=0;
};

#endif