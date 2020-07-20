#ifndef NAIVE_INTERSECTOR_HPP
#define NAIVE_INTERSECTOR_HPP
#include "intersector.hpp"
#include "../ray.hpp"
#include "../scene.hpp"
#include "../primitive/primitive.hpp"
#include <vector>

class NaiveIntersector: public Intersector {
    private:
        Scene* scene;
    public:
        NaiveIntersector(Scene* scene);
        double getIntersect(Ray ray, Vector3 *intersect, Vector3 *normal, Primitive **primitive);
        bool getShadowIntersect(Ray ray, double maxDistance);
};

#endif
