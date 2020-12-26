#ifndef NAIVE_INTERSECTOR_HPP
#define NAIVE_INTERSECTOR_HPP

#include "intersector.hpp"
#include "scene.hpp"
#include <random>
#include <vector>

class NaiveIntersector: public Intersector {
    public:
        NaiveIntersector(Scene* const scene);
        bool getIntersect(const Ray ray, Intersection& intersection) const;
};

#endif
