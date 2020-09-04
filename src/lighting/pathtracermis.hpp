#ifndef PATHTRACERMIS_HPP
#define PATHTRACERMIS_HPP

#include "lighting_model.hpp"
#include <random>

class PathTracerMIS: public LightingModel {
    public:
        PathTracerMIS(Intersector& intersector, const int maxDepth, const Vector3 ambient=Vector3(0.));
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;
        Vector3 evaluate(const Ray ray, const int depth, const Intersection& lastIntersection);
};

#endif