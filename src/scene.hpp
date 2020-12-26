#ifndef SCENE_HPP
#define SCENE_HPP

#include "primitive.hpp"
#include "complex_primitive.hpp"
#include "camera.hpp"
#include <variant>
#include <vector>

class Scene {
    public:
        std::vector<Primitive*> primitives;
        std::vector<Primitive*> lights;
        Scene();
        void insert(const std::variant<Primitive*, ComplexPrimitive*> object);
};

#endif