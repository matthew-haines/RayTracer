#ifndef LIGHTING_MODEL_HPP
#define LIGHTING_MODEL_HPP
#include "point_light.hpp"
#include "ray.hpp"
#include "surface.hpp"
#include "primitive.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include "intersector.hpp"
#include "constants.hpp"
#include <math.h>
#include <vector>

class SimpleLightingModel {
    private:
        Color ambient;
        Surface *medium;
        Intersector *intersector;
        std::vector<PointLight> lights;
        int maxDepth;
    public:
        SimpleLightingModel(Color ambient, Surface *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth);
        Color evaluate(Ray ray, int depth);
};

#endif