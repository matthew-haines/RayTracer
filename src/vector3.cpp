#include "vector3.hpp"
#include "matrix3.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>

Vector3::Vector3(double _x, double _y, double _z) {
    //data.d4 = _mm256_set_pd(0, _z, _y, _x); // little endian
    data.d[0] = _x;
    data.d[1] = _y;
    data.d[2] = _z;
}

Vector3::Vector3(double _x) {
    //data.d4 = _mm256_set_pd(0, _x, _x, _x);
    data.d[0] = _x;
    data.d[1] = _x;
    data.d[2] = _x;
}

Vector3::Vector3(__m256d dat) {
    data.d4 = dat;
}

double Vector3::x() {
    return data.d[0];
}

double Vector3::y() {
    return data.d[1];
}

double Vector3::z() {
    return data.d[2];
}

Vector3& Vector3::operator+=(Vector3 vec) {
    data.d4 = _mm256_add_pd(data.d4, vec.data.d4);
    return *this;
}

Vector3& Vector3::operator-=(Vector3 vec) {
    data.d4 = _mm256_sub_pd(data.d4, vec.data.d4);
    return *this;
}

Vector3& Vector3::operator*=(Vector3 vec) {
    data.d4 = _mm256_mul_pd(data.d4, vec.data.d4);
    return *this;
}

Vector3& Vector3::operator/=(Vector3 vec) {
    data.d4 = _mm256_div_pd(data.d4, vec.data.d4);
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
    __m256d in = _mm256_set_pd(0, a, a, a);
    data.d4 = _mm256_add_pd(data.d4, in);
    return *this;
}

Vector3& Vector3::operator-=(double a) {
    __m256d in = _mm256_set_pd(0, a, a, a);
    data.d4 = _mm256_sub_pd(data.d4, in);
    return *this;
}

Vector3& Vector3::operator*=(double a) {
    __m256d in = _mm256_set_pd(0, a, a, a);
    data.d4 = _mm256_mul_pd(data.d4, in);
    return *this;
}

Vector3& Vector3::operator/=(double a) {
    __m256d in = _mm256_set_pd(0, a, a, a);
    data.d4 = _mm256_div_pd(data.d4, in);
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
    if (index == 0) {
        return data.d[0];
    } else if (index == 1) {
        return data.d[1];
    } else {
        return data.d[2];
    }
}

double Vector3::dot(Vector3 vec) {
    return x() * vec.x() + y() * vec.y() + z() * vec.z();
}

Vector3 Vector3::cross(Vector3 vec) {
    // https://geometrian.com/programming/tutorials/cross-product/index.php
    __m256d tmp0 = _mm256_permute4x64_pd(vec.data.d4, _MM_SHUFFLE(3, 0, 2, 1));
    __m256d tmp1 = _mm256_permute4x64_pd(data.d4, _MM_SHUFFLE(3, 0, 2, 1));
    tmp0 = _mm256_mul_pd(tmp0, data.d4);
    tmp1 = _mm256_mul_pd(tmp1, vec.data.d4);
    __m256d tmp2 = _mm256_sub_pd(tmp0, tmp1);
    return Vector3(_mm256_permute4x64_pd(tmp2, _MM_SHUFFLE(3, 0, 2, 1)));
}

double Vector3::length() {
    return std::sqrt(x() * x() + y() * y() + z() * z());
}

double Vector3::max() {
    return std::max(x(), std::max(y(), z()));
}

double Vector3::min() {
    return std::min(x(), std::min(y(), z()));
}


void Vector3::normalize() {
    double magnitude = length();
    data.d[0] /= magnitude;
    data.d[1] /= magnitude;
    data.d[2] /= magnitude;
}

Vector3 Vector3::normalized() {
    double magnitude = length();
    return Vector3(x() / magnitude, y() / magnitude, z() / magnitude);
}

Vector3 operator-(Vector3& v) {
    return Vector3(-v.x(), -v.y(), -v.z());
}

bool operator==(Vector3 a, Vector3 b) {
    return (a.x() == b.x()) && (a.y() == b.y()) && (a.z() == b.z());
}

Vector3 operator*(Matrix3 a, Vector3 b) {
    return Vector3(a.x11 * b.x() + a.x12 * b.y() + a.x13 * b.z(), a.x21 * b.x() + a.x22 * b.y() + a.x23 * b.z(), a.x31 * b.x() + a.x32 * b.y() + a.x33 * b.z());
}

Vector3 SphericalToCartesian(Vector3 vec) {
    // (r, theta [0, pi], phi [0, 2pi])
    return Vector3(vec.x() * std::sin(vec.y()) * std::cos(vec.z()), vec.x() * std::sin(vec.y()) * std::sin(vec.z()), vec.x() * std::cos(vec.y()));
}

Vector3 CartesianToSpherical(Vector3 vec) {
    // (r, inclination, azimuth)
    return Vector3(vec.length(), atan2(sqrt(vec.x() * vec.x() + vec.y() * vec.y()), vec.z()), atan2(vec.y(), vec.x()));
}

Vector3 Vector3::max(Vector3 a, Vector3 b) {
    return Vector3(std::max(a.x(), b.x()), std::max(a.y(), b.y()), std::max(a.z(), b.z()));
}

Vector3 Vector3::min(Vector3 a, Vector3 b) {
    return Vector3(std::min(a.x(), b.x()), std::min(a.y(), b.y()), std::min(a.z(), b.z()));
}