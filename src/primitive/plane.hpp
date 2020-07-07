#ifndef PLANE_HPP
#define PLANE_HPP
#include "primitive.hpp"

class Plane: public Primitive {
    private:
        // Ax + Bx + Cx + D = 0
        Vector3 planeNormal;
        double d;
        bool oneSided;
    public:
        Plane(Vector3 planeNormal, double d, Material *material, bool oneSided=true);
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
};

#endif