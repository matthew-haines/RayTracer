#include "color.hpp"
#include "ray.hpp"
#include "surface.hpp"
#include "lighting_models.hpp"
#include "point_light.hpp"
#include "naive_intersector.hpp"
#include "constants.hpp"
#include "primitive.hpp"
#include <vector>

Color ambient(0.1, 0.1, 0.1);

int main() {
    std::vector<PointLight> lights; 
    std::vector<Primitive*> primitives;
    

    NaiveIntersector intersector(primitives);
    SimpleLightingModel lightingModel(ambient, &vacuum, &intersector, lights, 4);
}