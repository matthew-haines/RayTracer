#ifndef PATHTRACERMIS_HPP
#define PATHTRACERMIS_HPP

#include "lighting_model.hpp"
#include <random>

class PathTracerMIS: public LightingModel {
    public:
        PathTracerMIS(Intersector& intersector, int maxDepth, Vector3 ambient=Vector3(0.));
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;
        Vector3 evaluate(Ray ray, int depth, Intersection& lastIntersection);
};

#endif