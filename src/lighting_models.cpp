#include "lighting_models.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "surface.hpp"
#include "primitive.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include "intersector.hpp"
#include "constants.hpp"
#include <math.h>
#include <vector>

SimpleLightingModel::SimpleLightingModel(Color ambient, Surface *medium, Intersector *intersector, std::vector<PointLight> lights, int maxDepth=4): ambient(ambient), medium(medium), intersector(intersector), lights(lights), maxDepth(maxDepth) {}

Color SimpleLightingModel::evaluate(Ray ray, int depth) {
    Vector3 intersect, normal;
    Primitive *primitive;
    double distance = intersector->getIntersect(ray, &intersect, &normal, &primitive);
    if (distance == -1) {
        return ambient; 
    }
    Color color(0.0, 0.0, 0.0);
    if (primitive->surface->diffuse_coefficient != 0.0) {
        for (PointLight light : lights) {
            Vector3 direction = light.position - intersect;
            double lightDistance = direction.length();
            direction.normalize();
            double normalDotLight = normal.dot(direction);
            if (normalDotLight > -epsilon) {
                Ray shadowRay = {intersect, direction};
                if (intersector->getShadowIntersect(shadowRay, lightDistance)) {
                    color += primitive->surface->color * light.color * normalDotLight;
                }
            }
        }
        color *= primitive->surface->diffuse_coefficient;
    }
    if (depth < maxDepth) {
        // Reflection
        if (primitive->surface->specular_coefficient != 0.0) {
            Ray reflectionRay = {intersect, ray.direction - normal * 2.0 * ray.direction.dot(normal)};
            color += evaluate(reflectionRay, depth+1) * primitive->surface->specular_coefficient;
        }
        // Transmission
        if (primitive->surface->transmission_coefficient != 0.0) {
            double relativeRefraction;
            double c1 = ray.direction.dot(normal);
            if (c1 < 0.0) {
                relativeRefraction = medium->refraction_index / primitive->surface->refraction_index;
            }
            else {
                relativeRefraction = primitive->surface->refraction_index / medium->refraction_index;
            }
            double c22 = 1.0 - relativeRefraction * relativeRefraction * (1.0 - c1 * c1);
            if (c22 > -epsilon) {
                color += evaluate({intersect, ray.direction * relativeRefraction + normal * relativeRefraction * c1 - sqrt(c22)}, depth+1);
            }
        }
    }
    return color;
}