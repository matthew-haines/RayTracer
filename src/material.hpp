#ifndef MATERIAL_HPP 
#define MATERIAL_HPP
#include "vector3.hpp"

typedef struct material {
    // for simple (should probably find a different way to do this eventually)
    double diffuse_coefficient;
    double specular_coefficient;
    double transmission_coefficient;
    double refraction_index; 
    // for disney
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
    // for custom
    double ggx_alpha;
    Vector3 color;
    material(): emission(0.0), metallic(0.0), subsurface(0.0), specular(0.5), roughness(0.5), specularTint(0.0), sheen(0.0), sheenTint(0.5), clearcoat(0.0), clearcoatGloss(1.0) {};
} Material;

#endif