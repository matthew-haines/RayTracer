#ifndef ADVANCED_LIGHTING_MODEL_HPP
#define ADVANCED_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "intersector.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "vector3.hpp"
#include <vector>

class AdvancedLightingModel: public LightingModel {
    private:
        Vector3 ambient;
        Material *medium;
        Intersector *intersector;
        std::vector<PointLight> lights;
        int maxDepth;
        double SchlickFresnel(double u);
        double GTR1(double NdotH, double a);
        double GTR2(double NdotH, double a);
        double SmithG_GGX(double NdotV, double alphaG);
        Vector3 BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material);
    public:
        AdvancedLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif