#include "sphere.hpp"
#include "../constants.hpp"
#include "../helpers.hpp"
#include "../matrix3.hpp"
#include <cmath>

Sphere::Sphere(Vector3 center, double radius, Material *material): Primitive(material), center(center), radius(radius) {
    radius2 = radius * radius;
}

double Sphere::Intersect(Ray ray, Vector3 *intersect, Vector3 *normal) {
    Vector3 distance = center - ray.origin;
    double distance2 = distance.dot(distance);
    double lengthToClosest = distance.dot(ray.direction);
    if (lengthToClosest < -epsilon) {
        return -1;
    }
    double halfChordDistance2 = radius2 - distance2 + lengthToClosest * lengthToClosest;
    if (halfChordDistance2 < -epsilon) {
        return -1;
    }
    double intersectDistance;
    if (distance2 > radius2) {
        // Ray outside sphere
        intersectDistance = lengthToClosest - std::sqrt(halfChordDistance2);
    } else {
        // Ray inside sphere
        intersectDistance = lengthToClosest + std::sqrt(halfChordDistance2);
    }
    *intersect = ray.direction * intersectDistance + ray.origin;
    *normal = (*intersect - center) / radius;
    return intersectDistance;
};

Vector3 Sphere::Sample(double u1, double u2, double& probability) {
    Vector3 sample = UniformSampleSphere::sample(u1, u2);
    probability = UniformSampleSphere::pdf(sample);
    return radius * sample + center;
}

Vector3 Sphere::DirectionalSample(double u1, double u2, Vector3 point, double& probability) {
    Vector3 direction = center - point;
    double distance2 = direction.dot(direction);
    if (distance2 < radius2) {
        // sample uniformly
        return Sample(u1, u2, probability);
    } else {    
        double thetaMax = std::asin(std::sqrt(radius2 / distance2));
        double alt = M_PI_2 - thetaMax * u1;
        double azi = 2 * M_PI * u2; 
        Vector3 result = SphericalToCartesian(Vector3(1, azi, alt));
        probability = 1 / (2. * M_PI * (1. - std::cos(thetaMax)));
        Vector3 directional = (Matrix3::createFromNormal(direction.normalized()) * Vector3(result.z, result.y, result.x));
        // im done with efficiency for the day
        
    }
}