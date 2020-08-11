#ifndef BOUND_HPP
#define BOUND_HPP
#include "../vector3.hpp"

struct Bound {
    Vector3 min;
    Vector3 max;
    Vector3 centroid;
    Bound();
    Bound(Vector3 min, Vector3 max);
    double SurfaceArea();
    static Bound Union(Bound a, Bound b);
};

#endif