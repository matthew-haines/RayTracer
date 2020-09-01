#include "vector2.hpp"
#include <cmath>

Vector2::Vector2(double x, double y): x(x), y(y) {}

Vector2::Vector2(double x): x(x), y(x) {}

Vector2& Vector2::operator+=(Vector2 vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2& Vector2::operator-=(Vector2 vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2& Vector2::operator*=(Vector2 vec) {
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Vector2& Vector2::operator/=(Vector2 vec) {
    x /= vec.x;
    y /= vec.y;
    return *this;
}

Vector2 operator+(Vector2 a, Vector2 b) {
    Vector2 c = a;
    return c += b;
}

Vector2 operator-(Vector2 a, Vector2 b) {
    Vector2 c = a;
    return c -= b;
}

Vector2 operator*(Vector2 a, Vector2 b) {
    Vector2 c = a;
    return c *= b;
}

Vector2 operator/(Vector2 a, Vector2 b) {
    Vector2 c = a;
    return c /= b;
}

Vector2& Vector2::operator+=(double a) {
    x += a;
    y += a;
    return *this;
}

Vector2& Vector2::operator-=(double a) {
    x -= a;
    y -= a;
    return *this;
}

Vector2& Vector2::operator*=(double a) {
    x *= a;
    y *= a;
    return *this;
}

Vector2& Vector2::operator/=(double a) {
    x /= a;
    y /= a;
    return *this;
}

Vector2 operator+(Vector2 a, double b) {
    Vector2 c = a;
    return c += b;
}

Vector2 operator-(Vector2 a, double b) {
    Vector2 c = a;
    return c -= b;
}

Vector2 operator*(Vector2 a, double b) {
    Vector2 c = a;
    return c *= b;
}

Vector2 operator/(Vector2 a, double b) {
    Vector2 c = a;
    return c /= b;
}

double Vector2::dot(Vector2 vec) {
    return x * vec.x + y * vec.y;
}

double Vector2::length() {
    return std::sqrt(x * x + y * y);
}

void Vector2::normalize() {
    double magnitude = length();
    x /= magnitude;
    y /= magnitude;
}

Vector2 Vector2::normalized() {
    double magnitude = length();
    return Vector2(x / magnitude, y / magnitude);
}

Vector2 operator-(Vector2& v) {
    return Vector2(-v.x, -v.y);
}

bool operator==(Vector2 a, Vector2 b) {
    return (a.x == b.x) && (a.y == b.y);
}