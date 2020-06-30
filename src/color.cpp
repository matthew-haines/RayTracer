#include "color.hpp"

Color& Color::operator*=(Color c) {
    r *= c.r;
    g *= c.g;
    b *= c.b;
}

Color& Color::operator*=(double f) {
    r *= f;
    g *= f;
    b *= f;
}

Color& Color::operator+=(Color c) {
    r += c.r;
    g += c.g;
    b += c.b;
}

Color operator*(Color a, Color b) {
    Color c = a;
    return c *= b;
}

Color operator*(Color a, double b) {
    Color c = a;
    return c *= b;
}

Color operator+(Color a, Color b) {
    Color c = a;
    return c += b;
}

char ColorToChar(double color) {
    return (char)(std::min(color, 1.0) * 255);
}