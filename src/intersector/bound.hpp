#ifndef BOUND_HPP
#define BOUND_HPP

#include "../ray.hpp"

struct Bound {
    Vector3 min;
    Vector3 max;
    Vector3 centroid;
    Bound();
    Bound(Vector3 min, Vector3 max);
    double surfaceArea();
    static Bound computeUnion(Bound& a, Bound& b);
    static Bound computeUnion(Bound& a, Vector3& b);
    Vector3& operator[](int index);
    bool rayIntersect(Ray& ray, Vector3& invDir, const int dirIsNeg[3]);
};

#endif