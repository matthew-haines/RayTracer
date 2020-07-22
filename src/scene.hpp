#ifndef SCENE_HPP
#define SCENE_HPP
#include "primitive/primitive.hpp"
#include "primitive/complex_primitive.hpp"
#include <variant>
#include <vector>

class Scene {
    public:
        std::vector<Primitive*> primitives;
        std::vector<Primitive*> lights;
        Scene();
        void Insert(std::variant<Primitive*, ComplexPrimitive*> object);
};

#endif