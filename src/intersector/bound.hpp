#ifndef BOUND_HPP
#define BOUND_HPP
#include "../ray.hpp"
#include "../vector3.hpp"

struct Bound {
    Vector3 min;
    Vector3 max;
    Vector3 centroid;
    Bound();
    Bound(Vector3 min, Vector3 max);
    double SurfaceArea();
    static Bound Union(Bound a, Bound b);
    static Bound Union(Bound a, Vector3 b);
    Vector3& operator[](int index);
    bool RayIntersect(Ray& ray, Vector3& invDir, const int dirIsNeg[3]);
};

#endif