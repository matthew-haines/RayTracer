#ifndef MATERIAL_HPP 
#define MATERIAL_HPP

#include "bxdf.hpp"
#include "texture.hpp"

typedef struct material {
    double emission;
    BxDF* bxdf;
    Texture* texture;
    Vector3 color;
    material(): emission(0.0) {};
} Material;

#endif