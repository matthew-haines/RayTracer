#ifndef SIMPLE_LIGHTING_MODEL_HPP
#define SIMPLE_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "primitive.hpp"
#include "vector3.hpp"
#include "intersector.hpp"
#include "constants.hpp"
#include <math.h>
#include <vector>

class SimpleLightingModel: public LightingModel {
    private:
        Vector3 ambient;
        Material *medium;
        Intersector *intersector;
        std::vector<PointLight> lights;
        int maxDepth;
    public:
        SimpleLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif