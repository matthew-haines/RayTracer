#include "bound.hpp"
#include <algorithm>
#include <limits>

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