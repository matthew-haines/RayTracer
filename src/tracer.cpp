#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include "primitive.hpp"
#include "vector3.hpp"
#include "triangle.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "constants.hpp"

#define MAX_DEPTH 4

using namespace std;

vector<PointLight> lights;
vector<Primitive*> primitives; 
Color ambient(0.5, 0.5, 0.5);

bool ShadowTest(Ray ray, double distance) {
    Vector3 intersect, normal;
    for (Primitive* primitive : primitives) {
        if (primitive->intersect(ray, &intersect, &normal) < distance) {
            return false;
        }
    }
    return true;
}

Color RayTrace(Ray ray, int depth, Surface medium) {
    double minDistance = numeric_limits<double>::max();
    Primitive* closestPrimitive;
    Vector3 closestIntersect, closestNormal;
    for (Primitive* primitive : primitives) {
        Vector3 intersect, normal;
        double distance = primitive->intersect(ray, &intersect, &normal);
        if (distance > -epsilon && distance < minDistance) {
            closestPrimitive = primitive;
            minDistance = distance;
            closestIntersect = intersect;
            closestNormal = normal;
        }
    }
    if (minDistance == numeric_limits<double>::max()) {
        return ambient; // This is probably not right
    }
    else {
        // Hall model
        Color color(0.0, 0.0, 0.0);
        // Shadow Ray Tracing
        for (PointLight light : lights) {
            Vector3 lightDirection = light.position - closestIntersect;
            double lightDistance = lightDirection.length();
            lightDirection.normalize();
            double normalDotLight = closestNormal.dot(lightDirection);
            if (normalDotLight > -epsilon) {
                Ray shadowRay = {closestIntersect, lightDirection};
                if (ShadowTest(shadowRay, lightDistance)) {
                    color *= normalDotLight;
                    color += light.color * normalDotLight;
                }
            }
        }
        if (depth < MAX_DEPTH) {
            // Specular Reflection
            Ray reflectionRay = {closestIntersect, ray.direction - closestNormal * 2.0 * ray.direction.dot(closestNormal)};
            color += RayTrace(reflectionRay, depth + 1, medium) * closestPrimitive->surface->specular_coefficient;
            // Specular Refraction 
            double relativeRefraction = closestPrimitive->surface->refraction_index / medium.refraction_index;
            double c1 = -ray.direction.dot(closestNormal);
            double c22 = 1.0 - relativeRefraction * relativeRefraction * (1.0 - c1 * c1);
            if (c22 > -epsilon) {
                Ray refractionRay = {closestIntersect, ray.direction * relativeRefraction + closestNormal * relativeRefraction * c1 - sqrt(c22)};
                color += RayTrace(refractionRay, depth + 1, *closestPrimitive->surface) * closestPrimitive->surface->transmission_coefficient;
            }
        }
        return color;
    }
}

int main() {

    return 0;
}