#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "ray.hpp"
#include "primitive.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include "intersector.hpp"
#include <vector>

class SimpleLightingModel {
    private:
        Color ambient;
        Intersector *intersector;
        std::vector<PointLight> lights;
        int maxDepth;
    public:
        SimpleLightingModel(Color ambient, Intersector *intersector, std::vector<PointLight> lights, int maxDepth);
        Color evaluate(Ray ray, int depth);
};

#endif