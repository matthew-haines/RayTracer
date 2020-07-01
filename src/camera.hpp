#ifndef CAMAERA_HPP
#define CAMAERA_HPP
#include "color.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include <functional>

class Camera {
    public:
        virtual void generate(std::function<Color(Ray, int, Surface)>, Surface)=0;
        virtual void write(char*)=0;
};

#endif
