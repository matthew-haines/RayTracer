#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "../ray.hpp"
#include "../vector3.hpp"

class LightingModel {
    public:
        virtual Vector3 Evaluate(Ray ray, int depth)=0;
};

#endif