#include "scene.hpp"
#include <algorithm>

Scene::Scene() {
    primitives = std::vector<Primitive*>();    
    lights = std::vector<Primitive*>();
}

void Scene::Insert(std::variant<Primitive*, ComplexPrimitive*> object) {    
    if (std::holds_alternative<Primitive*>(object)) {
        Primitive* primitive = std::get<Primitive*>(object);
        if (primitive->material->emission != 0.) {
            lights.push_back(primitive);
        }
        primitives.push_back(primitive);
    } else {
        ComplexPrimitive* complexPrimitive = std::get<ComplexPrimitive*>(object);
        primitives.insert(primitives.end(), complexPrimitive->primitives.begin(), complexPrimitive->primitives.end());
        for (Primitive* primitive : complexPrimitive->primitives) {
            if (primitive->material->emission != 0.) {
                lights.push_back(primitive);
            }
        }
    }
}