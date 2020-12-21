#ifndef MATERIAL_HPP 
#define MATERIAL_HPP

#include "bxdf.hpp"
#include "texture.hpp"

struct Material {
    double emission;
    BxDF* bxdf;
    TextureMap* textureMap;
    Material(): emission(0.0) {};
};

#endif