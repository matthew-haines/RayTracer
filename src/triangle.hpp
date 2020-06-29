#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "primitive.hpp"
#include "vector3.hpp"

class Triangle: Primitive {
    private:
        Vector3 v0, v1, v2;
    public:
        Triangle(Vector3 v0, Vector3 v1, Vector3 v2);
        double intersect(Ray ray, Vector3 *intersectPoint, Vector3 *normal);
};

#endif
