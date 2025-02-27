#include "vector3.hpp"
#include "matrix3.hpp"
#include <algorithm>
#include <cmath>

Vector3::Vector3(double x, double y, double z): x(x), y(y), z(z) {}

Vector3::Vector3(double x): x(x), y(x), z(x) {}

Vector3& Vector3::operator+=(const Vector3 vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3 vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3 vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3 vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

Vector3 operator+(const Vector3 a, const Vector3 b) {
    Vector3 c = a;
    return c += b;
}

Vector3 operator-(const Vector3 a, const Vector3 b) {
    Vector3 c = a;
    return c -= b;
}

Vector3 operator*(const Vector3 a, const Vector3 b) {
    Vector3 c = a;
    return c *= b;
}

Vector3 operator/(const Vector3 a, const Vector3 b) {
    Vector3 c = a;
    return c /= b;
}

Vector3& Vector3::operator+=(const double a) {
    x += a;
    y += a;
    z += a;
    return *this;
}

Vector3& Vector3::operator-=(const double a) {
    x -= a;
    y -= a;
    z -= a;
    return *this;
}

Vector3& Vector3::operator*=(const double a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector3& Vector3::operator/=(const double a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

Vector3 operator+(const Vector3 a, const double b) {
    Vector3 c = a;
    return c += b;
}

Vector3 operator-(const Vector3 a, const double b) {
    Vector3 c = a;
    return c -= b;
}

Vector3 operator*(const Vector3 a, const double b) {
    Vector3 c = a;
    return c *= b;
}

Vector3 operator/(const Vector3 a, const double b) {
    Vector3 c = a;
    return c /= b;
}

double& Vector3::operator[](const int index) {
    if (index == 0) {
        return x;
    } else if (index == 1) {
        return y;
    } else {
        return z;
    }
}

double Vector3::dot(const Vector3 vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(const Vector3 vec) const {
    return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

double Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3::max() const {
    return std::max(x, std::max(y, z));
}

double Vector3::min() const {
    return std::min(x, std::min(y, z));
}


void Vector3::normalize() {
    double magnitude = length();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Vector3 Vector3::normalized() const {
    double magnitude = length();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 operator-(const Vector3& v) {
    return Vector3(-v.x, -v.y, -v.z);
}

bool operator==(const Vector3 a, const Vector3 b) {
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

bool operator!=(const Vector3 a, const Vector3 b) {
    return !(a == b);
}

Vector3 operator*(const Matrix3 a, const Vector3 b) {
    return Vector3(a.x11 * b.x + a.x12 * b.y + a.x13 * b.z, a.x21 * b.x + a.x22 * b.y + a.x23 * b.z, a.x31 * b.x + a.x32 * b.y + a.x33 * b.z);
}

// Converts from spherical coordinates in form (length, azimuth, polar angle) to cartesian coordinates in form (x, y, z)
Vector3 sphericalToCartesian(const Vector3 vec) {
    return Vector3(vec.x * std::sin(vec.z) * std::cos(vec.y), vec.x * std::sin(vec.z) * std::sin(vec.y), vec.x * std::cos(vec.z));
}

// Converts from cartesian coordinates in form (x, y, z) to spherical coordinates in form (length, azimuth, polar angle)
Vector3 cartesianToSpherical(const Vector3 vec) {
    return Vector3(vec.length(), atan2(vec.y, vec.x), atan2(sqrt(vec.x * vec.x + vec.y * vec.y), vec.z));
}

Vector3 Vector3::max(const Vector3 a, const Vector3 b) {
    return Vector3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Vector3 Vector3::min(const Vector3 a, const Vector3 b) {
    return Vector3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

void from_json(const nlohmann::json& j, Vector3& v) {
    j.at(0).get_to(v.x);
    j.at(1).get_to(v.y);
    j.at(2).get_to(v.z);
}