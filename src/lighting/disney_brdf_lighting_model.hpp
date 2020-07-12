#ifndef DISNEY_BRDF_LIGHTING_MODEL_HPP
#define DISNEY_BRDF_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "../intersector/intersector.hpp"
#include "../ray.hpp"
#include "../material.hpp"
#include "../vector3.hpp"
#include <random>

class DisneyBRDFLightingModel: public LightingModel {
    private:
        Vector3 ambient;
        Material *medium;
        Intersector *intersector;
        int maxDepth;
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
        double SchlickFresnel(double u);
        double GTR1(double NdotH, double a);
        double GTR2(double NdotH, double a);
        double SmithG_GGX(double NdotV, double alphaG);
        Vector3 BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material);
    public:
        DisneyBRDFLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif