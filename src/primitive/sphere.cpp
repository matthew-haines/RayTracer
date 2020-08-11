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

Vector3 Sphere::Sample(double u1, double u2) {
    Vector3 sample = UniformSampleSphere::sample(u1, u2);
    return radius * sample + center;
}

double Sphere::SamplePDF(Vector3 point, Vector3 direction) {
    return UniformSampleSphere::pdf(); 
}

Vector3 Sphere::DirectionalSample(double u1, double u2, Vector3 point) {
    Vector3 direction = center - point;
    double distance2 = direction.dot(direction);
    if (distance2 < radius2) {
        // sample uniformly
        return Sample(u1, u2);
    } else {    
        double thetaMax = std::asin(std::sqrt(radius2 / distance2));
        return UniformSampleCone::sample(u1, u2, direction, thetaMax);
    }
}

double Sphere::DirectionalSamplePDF(Vector3 point, Vector3 direction) {
    Vector3 distance = center - point;
    double distance2 = distance.dot(distance);
    if (distance2 < radius2) {
        return SamplePDF(point, direction);
    }
    double sinThetaMax2 = radius2 / distance2;
    double cosThetaMax = std::sqrt(std::max(0., 1-sinThetaMax2));
    if (direction.dot(distance.normalized()) < cosThetaMax) { // wont intersect
        return 0.;
    }
    return UniformSampleCone::pdf(cosThetaMax);
}

Bound Sphere::GetBound() {
    return Bound(center - Vector3(radius), center + Vector3(radius));
}