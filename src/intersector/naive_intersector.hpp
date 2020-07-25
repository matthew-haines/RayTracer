#ifndef NAIVE_INTERSECTOR_HPP
#define NAIVE_INTERSECTOR_HPP
#include "intersector.hpp"
#include "../ray.hpp"
#include "../scene.hpp"
#include "../primitive/primitive.hpp"
#include <random>
#include <vector>

class NaiveIntersector: public Intersector {
    private:
        Scene* scene;
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
    public:
        NaiveIntersector(Scene* scene);
        bool getIntersect(Ray ray, Intersection& intersection);
        bool getShadowIntersect(Ray ray, double maxDistance);
        Primitive& getRandomLight();
};

#endif
