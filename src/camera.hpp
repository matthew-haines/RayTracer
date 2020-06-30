#ifndef CAMAERA_HPP
#define CAMAERA_HPP
#include <functional>
#include "color.hpp"
#include "ray.hpp"

class Camera {
    public:
        virtual void generate(std::function<Color(Ray, int)>)=0;
        virtual void write(std::string)=0;
};

#endif
