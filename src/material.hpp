#ifndef MATERIAL_HPP 
#define MATERIAL_HPP
#include "vector3.hpp"

typedef struct material {
    double diffuse_coefficient, specular_coefficient, transmission_coefficient, refraction_index; // for simple (should probably find a different way to do this eventually)
    double metallic, subsurface, specular, roughness, specularTint, sheen, sheenTint, clearcoat, clearcoatGloss; 
    Vector3 color;
} Material;

#endif