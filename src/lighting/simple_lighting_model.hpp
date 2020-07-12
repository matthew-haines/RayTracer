#ifndef SIMPLE_LIGHTING_MODEL_HPP
#define SIMPLE_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "point_light.hpp"
#include "../ray.hpp"
#include "../material/material.hpp"
#include "../primitive/primitive.hpp"
#include "../vector3.hpp"
#include "../intersector/intersector.hpp"
#include "../constants.hpp"
#include <math.h>
#include <vector>

class SimpleLightingModel: public LightingModel {
    private:
        std::vector<PointLight> lights;
        Material *medium;
    public:
        SimpleLightingModel(Vector3 ambient, Intersector *intersector, int maxDepth, std::vector<PointLight> lights, Material *medium);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif