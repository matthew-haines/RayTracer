#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP

#include "intersection.hpp"
#include "scene.hpp"
#include <random>
#include <vector>

// Intersection base class.
class Intersector {
    protected:
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
    public:
        Scene* const scene;
        Intersector(Scene* const scene);
        // Intersection testing function, returns true if ray does intersect, else false.
        // intersection parameter is updated with information if it occurs.
        virtual bool getIntersect(const Ray ray, Intersection& intersection) const=0;
        Primitive* getRandomLight();
};

#endif
