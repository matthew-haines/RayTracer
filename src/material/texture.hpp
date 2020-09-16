#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "../vector3.hpp"
#include "../vector2.hpp"
#include <vector>

struct Texture {
    std::vector<Vector3>* const color;
    const std::size_t width, height;
    Texture()=default;
    Texture(std::vector<Vector3>* const color, const std::size_t width, const std::size_t height): color(color), width(width), height(height) {}
    Vector3& getColorAtUV(const Vector2& point) const {
        std::size_t column = width * point.x;
        std::size_t row = height * point.y;
        return color->at(row * width + column);
    };
    Texture& operator=(const Texture& t) {
        return Texture(t.color, t.width, t.height);
    }
};

#endif