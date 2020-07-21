#include "advanced_lighting_model.hpp"
#include "../helpers.hpp"
#include "../matrix3.hpp"
#include <math.h>

AdvancedLightingModel::AdvancedLightingModel(Vector3 ambient, Intersector *intersector, int maxDepth): LightingModel(ambient, intersector, maxDepth) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(0.0, 1.0);
}

double AdvancedLightingModel::Fresnel(double IdotM, double relativeIndex) {
    // ratio of reflected light
    double c = abs(IdotM);
    double g2 = relativeIndex * relativeIndex - 1. + c * c;
    if (g2 < 0.0) {
        return 1.0; // total internel reflection
    }
    double g = sqrt(g2);
    return 0.5 * square(g - c) / square(g + c) * (1. + square(c * (g+c) - 1.) / square(c * (g-c) + 1.));
}

double AdvancedLightingModel::SmithG(Vector3 v, Vector3 m, Vector3 n, double alpha2) {
    double VdotN = v.dot(n);
    if (v.dot(m) / VdotN <= 0.) {
        return 0.;
    } else {
        return 2. / (1 + sqrt(1. + alpha2 * square(tan(acos(VdotN)))));
    }
}

Vector3 AdvancedLightingModel::Evaluate(Ray ray, int depth) {
    Vector3 intersect, normal;
    Primitive *primitive;
    double distance = intersector->getIntersect(ray, &intersect, &normal, &primitive);
    if (distance == -1) {
        return ambient;
    }
    double IdotN = ray.direction.dot(-normal);
    double relativeRefraction = IdotN > 0. ? primitive->material->refraction_index : 1. / primitive->material->refraction_index;
    // Sample random microsurface normals from distribution and 2 random variables
    double alpha2 = square(primitive->material->ggx_alpha);

    double r1 = dis(gen);
    double r2 = dis(gen);
    double r3 = dis(gen);
    double theta = atan(primitive->material->ggx_alpha * sqrt(r1) / sqrt(1. - r1));
    double phi = 2. * M_PI * r2;
    Vector3 tx = ray.direction.cross(normal).normalized();
    Vector3 ty = tx.cross(normal).normalized();

    Vector3 m = sin(theta) * cos(phi) * tx + sin(theta) * sin(phi) * ty + cos(theta) * normal;

    double MdotN = m.dot(normal);
    // GGX
    double probability;
    if (MdotN <= 0.0) {
        probability = 0.0;
    } else {
        probability = alpha2 / (M_PI * square(square(cos(theta))) * square((alpha2 + square(tan(theta)))));
    }

    double IdotM = ray.direction.dot(-m); // may need to remove this negative I have literally no idea

    Ray newRay;

    double fresnel = Fresnel(IdotM, relativeRefraction);
    if (r3 <= fresnel) {
        // reflect
        newRay.direction = 2 * abs(IdotM) * m + ray.direction;
        newRay.origin = intersect + normal * 0.001;
    } else {
        // transmit
        newRay.direction = (relativeRefraction * IdotM - sign(IdotN) * sqrt(1 + square(relativeRefraction) * (square(IdotM) - 1.))) * m + relativeRefraction * ray.direction;
        newRay.origin = intersect - normal * 0.001;
    }

    // Smith 
    double G = SmithG(-ray.direction, m, normal, alpha2) * SmithG(newRay.direction, m, normal, alpha2);
    // Solve for weight of each sample with importance sampling 
}