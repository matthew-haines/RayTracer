#ifndef COLOR_HPP
#define COLOR_HPP
#include <algorithm>

class Color {
    public:
        double r, g, b;
        Color() = default;
        Color(double r, double g, double b): r(r), g(g), b(b) {};
        Color& operator*=(Color c);
        Color& operator*=(double f);
        Color& operator+=(Color c);
};

Color operator*(Color a, Color b);
Color operator*(Color a, double b);
Color operator+(Color a, Color b);

char ColorToChar(double color);

#endif