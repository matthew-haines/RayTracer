#include "primitive.hpp"
#include "vector3.hpp"
#include "sphere.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "constants.hpp"
#include "perspective_camera.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

#define MAX_DEPTH 16

using namespace std;

vector<PointLight> lights;
vector<Primitive*> primitives; 
Color ambient(0.1, 0.1, 0.1);

bool ShadowTest(Ray ray, double distance) {
    Vector3 intersect, normal;
    for (Primitive* primitive : primitives) {
        double intersectDistance = primitive->intersect(ray, &intersect, &normal);
        if (intersectDistance != -1) {
            if (intersectDistance < distance) {
                return false;
            }
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
                    color += light.color * normalDotLight;
                }
            }
        }
        if (depth < MAX_DEPTH) {
            // Specular Reflection
            if (closestPrimitive->surface->specular_coefficient != 0.0) {
                Ray reflectionRay = {closestIntersect, ray.direction - closestNormal * 2.0 * ray.direction.dot(closestNormal)};
                color += RayTrace(reflectionRay, depth + 1, medium) * closestPrimitive->surface->specular_coefficient;
            }
            // Specular Refraction 
            if (closestPrimitive->surface->transmission_coefficient != 0.0) {
                double relativeRefraction = closestPrimitive->surface->refraction_index / medium.refraction_index;
                double c1 = -ray.direction.dot(closestNormal);
                double c22 = 1.0 - relativeRefraction * relativeRefraction * (1.0 - c1 * c1);
                if (c22 > -epsilon) {
                    Ray refractionRay = {closestIntersect, ray.direction * relativeRefraction + closestNormal * relativeRefraction * c1 - sqrt(c22)};
                    color += RayTrace(refractionRay, depth + 1, *closestPrimitive->surface) * closestPrimitive->surface->transmission_coefficient;
                }
            }
        }
        return color;
    }
}

int main() {
    Surface vacuum = {0.0, 0.0, 0.0, 1.0, Color(0, 0.0, 0.0)};
    Surface sphereSurface = {0.5, 1.0, 0.0, 1.333, Color(0.5, 0.0, 0.0)};
    Surface sphereSurface2 = {0.1, 2.0, 0.5, 1.333, Color(0.0, 0.5, 0.0)};
    //lights.push_back({Vector3(0.0, -4.0, 4.0), Color(1.0, 0.0, 0.0)});
    //lights.push_back({Vector3(0.0, 4.0, 2.0), Color(0.0, 0.8, 0.0)});
    lights.push_back({Vector3(0.0, 0.0, 4.0), Color(1.0, 1.0, 1.0)});
    Sphere sphere(Vector3(5.0, -1.0, 2.0), 1);
    Sphere sphere2(Vector3(5.0, 1.0, -1), 1.2);
    Sphere sphere3(Vector3(7.0, -1.0, -1), 1.2);
    sphere.surface = &sphereSurface;
    sphere2.surface = &sphereSurface;
    sphere3.surface = &sphereSurface2;
    primitives.push_back(&sphere);
    primitives.push_back(&sphere2);
    primitives.push_back(&sphere3);
    PerspectiveCamera camera(1000, 1000, 3.1415/3, Vector3(0.0, 0.0, 0.0));
    std::function<Color(Ray, int, Surface)> raytrace = RayTrace;
    camera.generate(RayTrace, vacuum);
    camera.write("out.png");
    return 0;
}