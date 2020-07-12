#ifndef DISNEY_BSDF_LIGHTING_MODEL_HPP
#define DISNEY_BSDF_LIGHTING_MODEL_HPP
#include "lighting_model.hpp"
#include "../intersector/intersector.hpp"
#include "point_light.hpp"
#include "../ray.hpp"
#include "../material/material.hpp"
#include "../vector3.hpp"
#include <vector>

class DisneyBSDFLightingModel: public LightingModel {
    private:
        double SchlickFresnel(double u);
        double GTR1(double NdotH, double a);
        double GTR2(double NdotH, double a);
        double SmithG_GGX(double NdotV, double alphaG);
        Vector3 BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material);
    public:
        DisneyBSDFLightingModel(Vector3 ambient, Intersector *intersector, int maxDepth);
        Vector3 Evaluate(Ray ray, int depth);
};

#endif