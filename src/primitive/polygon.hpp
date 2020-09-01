#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "plane.hpp"

class Polygon: public Plane {
    private:
        std::vector<Vector3> *points;
    public:
        Polygon(Vector3 planeNormal, double d, Material *material, std::vector<Vector3> *points, bool oneSided=true);
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
};

#endif