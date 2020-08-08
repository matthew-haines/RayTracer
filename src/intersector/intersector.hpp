#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP
#include "../intersection.hpp"
#include "../scene.hpp"
#include "../primitive/primitive.hpp"
#include "../ray.hpp"
#include <vector>

class Intersector {
    public:
        Scene* scene;
        Intersector(Scene* scene): scene(scene) {};
        virtual bool getIntersect(Ray ray, Intersection& intersection)=0;
        virtual Primitive* getRandomLight()=0;
};

#endif
