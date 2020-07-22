#ifndef DISNEY_BRDF_LIGHTING_MODEL_HPP
#define DISNEY_BRDF_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "../vector3.hpp"
#include "../ray.hpp"
#include "../material/material.hpp"
#include <random>

class DisneyBRDFLightingModel: public LightingModel {
    private:
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
        double SchlickFresnel(double u);
        double GTR1(double NdotH, double a);
        double GTR2(double NdotH, double a);
        double SmithG_GGX(double NdotV, double alphaG);
        Vector3 BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material);
    public:
        DisneyBRDFLightingModel(Vector3 ambient, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif