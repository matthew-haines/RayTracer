#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP
#include "../intersection.hpp"
#include "../scene.hpp"
#include <random>
#include <vector>

class Intersector {
    protected:
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
    public:
        Scene* scene;
        Intersector(Scene* scene);
        virtual bool getIntersect(Ray ray, Intersection& intersection)=0;
        Primitive* getRandomLight();
};

#endif
