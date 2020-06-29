#include "vector3.hpp"
#include <math.h>

Vector3 Vector3::operator+(Vector3 vec) {
    return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(Vector3 vec) {
    return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(Vector3 vec) {
    return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

Vector3 Vector3::operator/(Vector3 vec) {
    return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

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

Vector3 Vector3::operator+(double a) {
    return Vector3(x + a, y + a, z + a);
}         

Vector3 Vector3::operator-(double a) {
    return Vector3(x - a, y - a, z - a);
}

Vector3 Vector3::operator*(double a) {
    return Vector3(x * a, y * a, z * a);
}

Vector3 Vector3::operator/(double a) {
    return Vector3(x / a, y / a, z / a);
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

bool Vector3::operator==(Vector3 vec) {
    return (x == vec.x) && (y == vec.y) && (z == vec.z);
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