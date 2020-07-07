#include "advanced_lighting_model.hpp"
#include "intersector.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <algorithm>
#include <math.h>
#include <vector>

AdvancedLightingModel::AdvancedLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth=4): ambient(ambient), medium(medium), intersector(intersector), lights(lights), maxDepth(maxDepth) {}

double AdvancedLightingModel::SchlickFresnel(double u) {
    double m = std::clamp(1 - u, 0.0, 1.0);
    return m * m * m * m * m;
}

double AdvancedLightingModel::GTR1(double NdotH, double a) {
    double a2 = a * a;
    return (a2 - 1.) / (M_PI * log(a2) * (1. + (a2 - 1.) * NdotH * NdotH)); // Make sure this log should be ln
}

double AdvancedLightingModel::GTR2(double NdotH, double a) {
    double a2 = a * a;
    double denom = 1. + (a2 - 1.) * NdotH * NdotH;
    return a2 / (M_PI * denom * denom);
}

double AdvancedLightingModel::SmithG_GGX(double NdotV, double alphaG) {
    float a = alphaG * alphaG;
    float b = NdotV * NdotV;
    return 1 / (NdotV + sqrt(a + b - a * b));
}

Vector3 AdvancedLightingModel::BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material) {
    double NdotL = N.dot(L);
    double NdotV = N.dot(V);
    if (NdotL < 0 || NdotV < 0) return Vector3(0.);

    Vector3 H = (L + V).normalized();
    double NdotH = N.dot(H);
    double LdotH = L.dot(H);

    double Cdlum = .3 * material->color.x + .6 * material->color.y + .1 * material->color.z;
    Vector3 Ctint = Cdlum > 0 ? material->color * (1/Cdlum) : Vector3(0.);
}

Vector3 AdvancedLightingModel::Evaluate(Ray ray, int depth) {
    
}