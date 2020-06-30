#include <math.h>
#include "vector3.hpp"
#include "matrix3.hpp"

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

Vector3 Vector3::normalized() {
    double magnitude = length();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 operator*(Matrix3 mat, Vector3 vec) {
    return Vector3(vec.dot(mat.r1), vec.dot(mat.r2), vec.dot(mat.r3));
}