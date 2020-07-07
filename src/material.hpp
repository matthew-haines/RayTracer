#ifndef MATERIAL_HPP 
#define MATERIAL_HPP
#include "vector3.hpp"

typedef struct material {
    double diffuse_coefficient;
    double specular_coefficient;
    double transmission_coefficient;
    double refraction_index; // for simple (should probably find a different way to do this eventually)
    double emission;
    double metallic;
    double subsurface;
    double specular;
    double roughness;
    double specularTint;
    double sheen;
    double sheenTint;
    double clearcoat;
    double clearcoatGloss;
    Vector3 color;
} Material;

#endif