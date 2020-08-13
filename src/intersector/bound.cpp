#include "bound.hpp"
#include <algorithm>
#include <limits>
#include <cassert>

Bound::Bound() {
    min = Vector3(std::numeric_limits<double>::max());
    max = Vector3(std::numeric_limits<double>::lowest());
    centroid = (min + max) / 2;
}

Bound::Bound(Vector3 min, Vector3 max): min(min), max(max) {
    centroid = (min + max) / 2;
}

double Bound::SurfaceArea() {
    double length = max.x - min.x;
    double width = max.y - min.y;
    double height = max.z - min.z;
    return 2. * (length * width + length * height + width * height);
}



Bound Bound::Union(Bound a, Bound b) {
    Vector3 min(std::min(a.min.x, b.min.x), std::min(a.min.y, b.min.y), std::min(a.min.z, b.min.z));
    Vector3 max(std::max(a.max.x, b.max.x), std::max(a.max.y, b.max.y), std::max(a.max.z, b.max.z));
    return Bound(min, max);
}

Vector3& Bound::operator[](int index) {
    assert(index == 0 || index == 1);
    switch (index) {
        case 0:
            return min;
        case 1:
            return max;
    }
}

bool Bound::RayIntersect(Ray& ray, Vector3& invDir, const int dirIsNeg[3]) {
    // Because of the strict performance requirements, I copied this from PBRT
    Bound& bound = *this;
    double tMin = (bound[dirIsNeg[0]].x - ray.origin.x) * invDir.x;
    double tMax = (bound[1-dirIsNeg[0]].x - ray.origin.x) * invDir.x;
    double tyMin = (bound[dirIsNeg[1]].y - ray.origin.y) * invDir.y;
    double tyMax = (bound[1-dirIsNeg[1]].y - ray.origin.y) * invDir.y;

    if (tMin > tyMax || tyMin > tMax) {
        return false;
    } 
    if (tyMin > tMin) {
        tMin = tyMin;
    } 
    if (tyMax < tMax) {
        tMax = tyMax;
    }

    double tzMin = (bound[dirIsNeg[2]].z - ray.origin.z) * invDir.z;
    double tzMax = (bound[1-dirIsNeg[2]].z - ray.origin.z) * invDir.z;
    if (tMin > tzMax || tzMin > tMax) {
        return false; 
    }
    if (tzMin > tMin) {
        tMin = tzMin; 
    }
    if (tzMax < tMax) {
        tMax = tzMax;
    }
    return tMax > 0;
}
