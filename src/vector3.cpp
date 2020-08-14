#include "vector3.hpp"
#include "matrix3.hpp"
#include <cmath>
#include <algorithm>
#include <cassert>

Vector3::Vector3(double x, double y, double z): x(x), y(y), z(z) {}

Vector3::Vector3(double x): x(x), y(x), z(x) {}

Vector3& Vector3::operator+=(Vector3 vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3& Vector3::operator-=(Vector3 vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3& Vector3::operator*=(Vector3 vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3& Vector3::operator/=(Vector3 vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
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
    return *this;
}

Vector3& Vector3::operator-=(double a) {
    x -= a;
    y -= a;
    z -= a;
    return *this;
}

Vector3& Vector3::operator*=(double a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector3& Vector3::operator/=(double a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
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

double& Vector3::operator[](int index) {
    assert(index == 0 || index == 1 || index == 2);
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

double Vector3::dot(Vector3 vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(Vector3 vec) {
    return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

double Vector3::length() {
    return std::sqrt(x * x + y * y + z * z);
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

Vector3 operator-(Vector3& v) {
    return Vector3(-v.x, -v.y, -v.z);
}

bool operator==(Vector3 a, Vector3 b) {
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

Vector3 operator*(Matrix3 a, Vector3 b) {
    return Vector3(a.x11 * b.x + a.x12 * b.y + a.x13 * b.z, a.x21 * b.x + a.x22 * b.y + a.x23 * b.z, a.x31 * b.x + a.x32 * b.y + a.x33 * b.z);
}

Vector3 SphericalToCartesian(Vector3 vec) {
    // (r, theta [0, pi], phi [0, 2pi])
    return Vector3(vec.x * std::sin(vec.y) * std::cos(vec.z), vec.x * std::sin(vec.y) * std::sin(vec.z), vec.x * std::cos(vec.y));
}

Vector3 CartesianToSpherical(Vector3 vec) {
    // (r, inclination, azimuth)
    return Vector3(vec.length(), atan2(sqrt(vec.x * vec.x + vec.y * vec.y), vec.z), atan2(vec.y, vec.x));
}

Vector3 Vector3::max(Vector3 a, Vector3 b) {
    return Vector3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Vector3 Vector3::min(Vector3 a, Vector3 b) {
    return Vector3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}