#ifndef ADVANCED_LIGHTING_MODEL_HPP
#define ADVANCED_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include <random>

class AdvancedLightingModel: public LightingModel {
    // https://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
        double Fresnel(double IdotM, double relativeIndex);
        double SmithG(Vector3 v, Vector3 m, Vector3 n, double ggx_alpha);
    public:
        AdvancedLightingModel(Vector3 ambient, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif
