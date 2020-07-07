#include "advanced_lighting_model.hpp"
#include "helpers.hpp"
#include "intersector.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <algorithm>
#include <math.h>
#include <vector>

AdvancedLightingModel::AdvancedLightingModel(Vector3 ambient, Material *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth=4): ambient(ambient), medium(medium), intersector(intersector), lights(lights), maxDepth(maxDepth) {}

double AdvancedLightingModel::SchlickFresnel(double theta) {
    double m = std::clamp(1.0 - theta, 0.0, 1.0);
    return m * m * m * m * m;
}

double AdvancedLightingModel::GTR1(double NdotH, double a) {
    double a2 = a * a;
    return (a2 - 1.0) / (M_PI * log(a2) * (1.0 + (a2 - 1.0) * NdotH * NdotH)); // Make sure this log should be ln
}

double AdvancedLightingModel::GTR2(double NdotH, double a) {
    double a2 = a * a;
    double denom = 1.0 + (a2 - 1.0) * NdotH * NdotH;
    return a2 / (M_PI * denom * denom);
}

double AdvancedLightingModel::SmithG_GGX(double NdotV, double alphaG) {
    float a = alphaG * alphaG;
    float b = NdotV * NdotV;
    return 1.0 / (NdotV + sqrt(a + b - a * b));
}

Vector3 AdvancedLightingModel::BRDF(Vector3 L, Vector3 V, Vector3 N, Material *material) {
    // Disney's BRDF
    double NdotL = N.dot(L);
    double NdotV = N.dot(V);
    if (NdotL < 0.0 || NdotV < 0.0) return Vector3(0.0);

    Vector3 H = (L + V).normalized();
    double NdotH = N.dot(H);
    double LdotH = L.dot(H);

    double Cdlum = 0.3 * material->color.x + 0.6 * material->color.y + 0.1 * material->color.z;

    Vector3 Ctint = Cdlum > 0.0 ? material->color * (1/Cdlum) : Vector3(0.0);
    Vector3 Cspec0 = mix(material->specular * 0.08 * mix(Vector3(1.0), Ctint, material->specularTint), material->color, material->metallic);
    Vector3 Csheen = mix(Vector3(1.), Ctint, material->sheenTint);

    double FL = SchlickFresnel(NdotL);
    double FV = SchlickFresnel(NdotV);
    double Fd90 = 0.5 + 2 * LdotH * LdotH * material->roughness;
    double Fd = mix(1.0, Fd90, FL) * mix(1.0, Fd90, FV);

    double Fss90 = LdotH * LdotH * material->roughness;
    double Fss = mix(1.0, Fss90, FL) * mix(1.0, Fss90, FV);
    double ss = 1.25 * (Fss * (1.0 / (NdotL + NdotV) - 0.5) + 0.5);

    double Ds = GTR2(NdotH, std::max(0.001, material->roughness));
    double FH = SchlickFresnel(LdotH);
    Vector3 Fs = mix(Cspec0, Vector3(1.0), FH);
    double roughg = square(material->roughness * 0.5 + 0.5);
    double Gs = SmithG_GGX(NdotL, roughg) * SmithG_GGX(NdotV, roughg);

    Vector3 Fsheen = FH * material->sheen * Csheen;

    double Dr = GTR1(NdotH, mix(0.1, 0.001, material->clearcoatGloss));
    double Fr = mix(0.04, 1.0, FH);
    double Gr = SmithG_GGX(NdotL, 0.25) * SmithG_GGX(NdotV, 0.25);

    return ((1/M_PI) * mix(Fd, ss, material->subsurface) * material->color + Fsheen) * (1.0 - material->metallic) + (Gs * Fs * Ds + 0.25 * material->clearcoat * Gr * Fr * Dr);
}

Vector3 AdvancedLightingModel::Evaluate(Ray ray, int depth) {
    
}