#include "lighting_models.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "primitive.hpp"
#include "color.hpp"
#include "vector3.hpp"
#include "intersector.hpp"
#include "constants.hpp"
#include <vector>

SimpleLightingModel::SimpleLightingModel(Color ambient, Intersector *intersector, std::vector<PointLight> lights, int maxDepth=4): ambient(ambient), intersector(intersector), lights(lights), maxDepth(maxDepth) {}

Color SimpleLightingModel::evaluate(Ray ray, int depth) {
    Vector3 intersect, normal;
    Primitive *primitive;
    double distance = intersector->getIntersect(ray, &intersect, &normal, &primitive);
    if (distance == -1) {
        return ambient; 
    }
    Color color(0.0, 0.0, 0.0);
    for (PointLight light : lights) {
        Vector3 direction = light.position - intersect;
        double lightDistance = direction.length();
        direction.normalize();
        double normalDotLight = normal.dot(direction);
        if (normalDotLight > -epsilon) {
            Ray shadowRay = {intersect, direction};
            if (intersector->getShadowIntersect(shadowRay, lightDistance)) {
                color += light.color * normalDotLight;
            }
        }
    }
    if (depth < maxDepth) {
        
    }
}