#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "primitive.hpp"
#include "../vector3.hpp"

class Triangle: public Primitive {
    private:
        Vector3 v0, v1, v2;
    public:
        Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Material *material);
        double intersect(Ray ray, Vector3 *intersect, Vector3 *normal);
};

#endif
