#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "../vector3.hpp"
#include "../ray.hpp"
#include "../intersector/intersector.hpp"

class LightingModel {
    protected:
        Vector3 ambient;
        Intersector *intersector;
        int maxDepth;
    public:
        LightingModel(Vector3 ambient, Intersector *intersector, int maxDepth): ambient(ambient), intersector(intersector), maxDepth(maxDepth) {};
        virtual Vector3 Evaluate(Ray ray, int depth)=0;
};

#endif