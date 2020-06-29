#include "color.hpp"

Color Color::operator*(Color c) {
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator*(double f) {
    return Color(r * f, g * f, b * f);
}

Color Color::operator+(Color c) {
    return Color(r + c.r, g + c.g, b + c.b);
}