#include "vector2.hpp"
#include <cmath>

Vector2::Vector2(double x, double y): x(x), y(y) {}

Vector2::Vector2(double x): x(x), y(x) {}

Vector2& Vector2::operator+=(const Vector2 vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2 vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2 vec) {
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2 vec) {
    x /= vec.x;
    y /= vec.y;
    return *this;
}

Vector2 operator+(const Vector2 a, const Vector2 b) {
    Vector2 c = a;
    return c += b;
}

Vector2 operator-(const Vector2 a, const Vector2 b) {
    Vector2 c = a;
    return c -= b;
}

Vector2 operator*(const Vector2 a, const Vector2 b) {
    Vector2 c = a;
    return c *= b;
}

Vector2 operator/(const Vector2 a, const Vector2 b) {
    Vector2 c = a;
    return c /= b;
}

Vector2& Vector2::operator+=(const double a) {
    x += a;
    y += a;
    return *this;
}

Vector2& Vector2::operator-=(const double a) {
    x -= a;
    y -= a;
    return *this;
}

Vector2& Vector2::operator*=(const double a) {
    x *= a;
    y *= a;
    return *this;
}

Vector2& Vector2::operator/=(const double a) {
    x /= a;
    y /= a;
    return *this;
}

Vector2 operator+(const Vector2 a, const double b) {
    Vector2 c = a;
    return c += b;
}

Vector2 operator-(const Vector2 a, const double b) {
    Vector2 c = a;
    return c -= b;
}

Vector2 operator*(const Vector2 a, const double b) {
    Vector2 c = a;
    return c *= b;
}

Vector2 operator/(const Vector2 a, const double b) {
    Vector2 c = a;
    return c /= b;
}

double Vector2::dot(const Vector2 vec) const {
    return x * vec.x + y * vec.y;
}

double Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2::normalize() {
    double magnitude = length();
    x /= magnitude;
    y /= magnitude;
}

Vector2 Vector2::normalized() const {
    double magnitude = length();
    return Vector2(x / magnitude, y / magnitude);
}

Vector2 operator-(const Vector2& v) {
    return Vector2(-v.x, -v.y);
}

bool operator==(const Vector2 a, const Vector2 b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Vector2 a, const Vector2 b) {
    return !(a == b);
}

void from_json(const nlohmann::json& j, Vector2& v) {
    j.at(0).get_to(v.x);
    j.at(1).get_to(v.y);
}