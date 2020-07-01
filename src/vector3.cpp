#include <math.h>
#include "vector3.hpp"

Vector3::Vector3(double x, double y, double z): x(x), y(y), z(y) {}

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
