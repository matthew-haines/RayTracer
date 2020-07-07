#include "vector3.hpp"
#include "matrix3.hpp"
#include <math.h>

Vector3::Vector3(double x, double y, double z): x(x), y(y), z(z) {}

Vector3::Vector3(double x): x(x), y(x), z(x) {}

Vector3& Vector3::operator+=(Vector3 vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

Vector3& Vector3::operator-=(Vector3 vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

Vector3& Vector3::operator*=(Vector3 vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
}

Vector3& Vector3::operator/=(Vector3 vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
}

Vector3 operator+(Vector3 a, Vector3 b) {
    Vector3 c = a;
    return c += b;
}

Vector3 operator-(Vector3 a, Vector3 b) {
    Vector3 c = a;
    return c -= b;
}

Vector3 operator*(Vector3 a, Vector3 b) {
    Vector3 c = a;
    return c *= b;
}

Vector3 operator/(Vector3 a, Vector3 b) {
    Vector3 c = a;
    return c /= b;
}

Vector3& Vector3::operator+=(double a) {
    x += a;
    y += a;
    z += a;
}

Vector3& Vector3::operator-=(double a) {
    x -= a;
    y -= a;
    z -= a;
}

Vector3& Vector3::operator*=(double a) {
    x *= a;
    y *= a;
    z *= a;
}

Vector3& Vector3::operator/=(double a) {
    x /= a;
    y /= a;
    z /= a;
}

Vector3 operator+(Vector3 a, double b) {
    Vector3 c = a;
    return c += b;
}

Vector3 operator-(Vector3 a, double b) {
    Vector3 c = a;
    return c -= b;
}

Vector3 operator*(Vector3 a, double b) {
    Vector3 c = a;
    return c *= b;
}

Vector3 operator/(Vector3 a, double b) {
    Vector3 c = a;
    return c /= b;
}

double Vector3::dot(Vector3 vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(Vector3 vec) {
    return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

double Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize() {
    double magnitude = length();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Vector3 Vector3::normalized() {
    double magnitude = length();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

bool operator==(Vector3 a, Vector3 b) {
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

Vector3 operator*(Matrix3 a, Vector3 b) {
    return Vector3(a.x11 * b.x + a.x12 * b.y + a.x13 * b.z, a.x21 * b.x + a.x22 * b.y + a.x23 * b.z, a.x31 * b.x + a.x32 * b.y + a.x33 * b.z);
}

Vector3 mix(Vector3 x, Vector3 y, double a) {
    return x * (1. - a) + y * a;
}

char ColorToChar(double color) {
    return (char)(std::min(color, 1.0) * 255);
}