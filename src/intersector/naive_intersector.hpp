#ifndef NAIVE_INTERSECTOR_HPP
#define NAIVE_INTERSECTOR_HPP
#include "intersector.hpp"
#include "../ray.hpp"
#include "../primitive/primitive.hpp"
#include <vector>

class NaiveIntersector: public Intersector {
    private:
        std::vector<Primitive*> primitives;
    public:
        NaiveIntersector(std::vector<Primitive*> primitives);
        double getIntersect(Ray ray, Vector3 *intersect, Vector3 *normal, Primitive **primitive);
        bool getShadowIntersect(Ray ray, double maxDistance);
};

#endif
