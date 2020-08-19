#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "../vector3.hpp"
#include "../ray.hpp"
#include "../intersector/intersector.hpp"
#include "../camera/camera.hpp"
#include <vector>

class LightingModel {
    protected:
        Intersector& intersector;
        int maxDepth;
        Vector3 ambient;
    public:
        LightingModel(Intersector& intersector, int maxDepth, Vector3 ambient);
        void Render(Camera& camera, int threads, int samples);
        virtual Vector3 Evaluate(Ray ray, int depth)=0;
};

#endif