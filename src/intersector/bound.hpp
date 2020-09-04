#ifndef BOUND_HPP
#define BOUND_HPP

#include "../ray.hpp"

struct Bound {
    Vector3 min;
    Vector3 max;
    Vector3 centroid;
    Bound();
    Bound(const Vector3 min, const Vector3 max);
    double surfaceArea();
    static Bound computeUnion(const Bound& a, const Bound& b);
    static Bound computeUnion(const Bound& a, const Vector3& b);
    const Vector3& operator[](const int index) const;
    bool rayIntersect(const Ray& ray, const Vector3& invDir, const int dirIsNeg[3]) const;
};

#endif