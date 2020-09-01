#ifndef MATERIAL_HPP 
#define MATERIAL_HPP
#include "bxdf.hpp"
#include "../vector3.hpp"

typedef struct material {
    double emission;
    BxDF* bxdf;
    Vector3 color;
    material(): emission(0.0) {};
} Material;

#endif