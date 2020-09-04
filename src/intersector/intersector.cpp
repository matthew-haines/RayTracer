#include "intersector.hpp"

Intersector::Intersector(Scene* const scene): scene(scene) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<int>(0, scene->lights.size()-1);
};

Primitive* Intersector::getRandomLight() {
    return &(*scene->lights[dist(gen)]);
}