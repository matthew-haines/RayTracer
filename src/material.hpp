#ifndef MATERIAL_HPP 
#define MATERIAL_HPP
#include "vector3.hpp"

typedef struct material {
    double diffuse_coefficient, specular_coefficient, transmission_coefficient, refraction_index;
    Vector3 color;
} Material;

#endif