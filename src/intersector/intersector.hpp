#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP

#include "intersection.hpp"
#include "scene.hpp"
#include <random>
#include <vector>

class Intersector {
    protected:
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
    public:
        Scene* const scene;
        Intersector(Scene* const scene);
        virtual bool getIntersect(const Ray ray, Intersection& intersection) const=0;
        Primitive* getRandomLight();
};

#endif
