#include "sphere.hpp"
#include "../constants.hpp"
#include "../helpers.hpp"
#include "../matrix3.hpp"
#include <cmath>

Sphere::Sphere(const Vector3 center, const double radius, Material* const material): Primitive(material), center(center), radius(radius), radius2(radius * radius) {
}

double Sphere::intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const {
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

Vector3 Sphere::sample(const double u1, const double u2) const {
    Vector3 sample = UniformSampleSphere::sample(u1, u2);
    return radius * sample + center;
}

double Sphere::samplePdf(const Vector3 point, const Vector3 direction) const {
    return UniformSampleSphere::pdf(); 
}

Vector3 Sphere::directionalSample(const double u1, const double u2, const Vector3 point) const {
    Vector3 direction = center - point;
    double distance2 = direction.dot(direction);
    if (distance2 < radius2) {
        // sample uniformly
        return sample(u1, u2);
    } else {    
        double thetaMax = std::asin(std::sqrt(radius2 / distance2));
        return UniformSampleCone::sample(u1, u2, direction, thetaMax);
    }
}

double Sphere::directionalSamplePdf(const Vector3 point, const Vector3 direction) const {
    Vector3 distance = center - point;
    double distance2 = distance.dot(distance);
    if (distance2 < radius2) {
        return samplePdf(point, direction);
    }
    double sinThetaMax2 = radius2 / distance2;
    double cosThetaMax = std::sqrt(std::max(0., 1-sinThetaMax2));
    if (direction.dot(distance.normalized()) < cosThetaMax) { // wont intersect
        return 0.;
    }
    return UniformSampleCone::pdf(cosThetaMax);
}

Bound Sphere::getBound() const {
    return Bound(center - Vector3(radius), center + Vector3(radius));
}

Vector2 Sphere::getUVAtPoint(const Vector3& point) const {
    Vector3 distance = point - center;
    double u = 0.5 + std::atan2(distance.x, distance.z) / (2 * M_PI);
    double v = 0.5 - std::asin(distance.y) / M_PI;
    return Vector2(u, v);
}