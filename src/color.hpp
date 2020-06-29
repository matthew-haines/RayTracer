#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
    public:
        double r, g, b;
        Color(double r, double g, double b): r(r), g(g), b(b) {};
        Color operator*(Color c);
        Color operator*(double f);
        Color operator+(Color c);
};

#endif