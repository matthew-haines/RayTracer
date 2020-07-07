#ifndef PLANE_HPP
#define PLANE_HPP
#include "primitive.hpp"

class Plane: public Primitive {
    private:
        Vector3 planeNormal;
        double d;
        bool oneSided;
    public:
        Plane(Vector3 planeNormal, double d, Material *material, bool oneSided);
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
};

#endif