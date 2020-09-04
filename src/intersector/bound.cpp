#include "bound.hpp"
#include <algorithm>
#include <limits>
#include <cassert>

Bound::Bound() {
    min = Vector3(std::numeric_limits<double>::max());
    max = Vector3(std::numeric_limits<double>::lowest());
    centroid = (min + max) / 2;
}

Bound::Bound(const Vector3 min, const Vector3 max): min(min), max(max) {
    centroid = (min + max) / 2;
}

double Bound::surfaceArea() {
    double length = max.x - min.x;
    double width = max.y - min.y;
    double height = max.z - min.z;
    return 2. * (length * width + length * height + width * height);
}

Bound Bound::computeUnion(const Bound& a, const Bound& b) {
    return Bound(Vector3::min(a.min, b.min), Vector3::max(a.max, b.max));
}

Bound Bound::computeUnion(const Bound& a, const Vector3& b) {
    return Bound(Vector3::min(a.min, b), Vector3::max(a.max, b));
}

const Vector3& Bound::operator[](const int index) const {
    if (index == 0) {
        return min;
    }
    return max;
}

bool Bound::rayIntersect(const Ray& ray, const Vector3& invDir, const int dirIsNeg[3]) const {
    // Because of the strict performance requirements, I copied this from PBRT
    const Bound& bound = *this;
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
