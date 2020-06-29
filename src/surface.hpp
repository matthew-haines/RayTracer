#ifndef SURFACE_HPP
#define SURFACE_HPP
#include "color.hpp"

typedef struct surface {
    double diffuse_coefficient, specular_coefficient, transmission_coefficient, refraction_index;
    Color color;
} Surface;

#endif