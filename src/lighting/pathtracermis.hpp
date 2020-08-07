#ifndef PATHTRACERMIS_HPP
#define PATHTRACERMIS_HPP
#include "lighting_model.hpp"
#include <random>

class PathTracerMIS: public LightingModel {
    public:
        PathTracerMIS(Intersector& intersector, int maxDepth, Vector3 ambient=Vector3(0.));
        std::vector<Vector3> Render(std::vector<Ray>& rays, int threads, int samples);
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;
        void EvaluateWrapper(int index, std::vector<Ray>& rays, std::vector<Vector3>& image, int samples);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif