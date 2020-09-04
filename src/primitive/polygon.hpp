#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "plane.hpp"

class Polygon: public Plane {
    private:
        std::vector<Vector3>* const points;
    public:
        Polygon(const Vector3 planeNormal, const double d, Material* const material, std::vector<Vector3>* const points, const bool oneSided=true);
        double intersect(const Ray ray, Vector3* const intersect, Vector3* const normal) const;
};

#endif