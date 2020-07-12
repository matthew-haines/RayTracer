#ifndef ADVANCED_LIGHTING_MODEL_HPP
#define ADVANCED_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "../material.hpp"
#include "../intersector/intersector.hpp"
#include <random>

class AdvancedLightingModel: public LightingModel {
    // https://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf
    private:
        Vector3 ambient;
        Material *medium;
        Intersector *intersector;
        int maxDepth;
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
        double Fresnel(double IdotM, double relativeIndex);
        double SmithG(Vector3 v, Vector3 m, Vector3 n, double ggx_alpha);
    public:
        AdvancedLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif
