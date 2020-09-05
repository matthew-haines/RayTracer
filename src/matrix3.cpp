#include "matrix3.hpp"
#include "vector3.hpp"
#include "helpers.hpp"
#include <cmath>

Matrix3::Matrix3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33) : x11(x11), x12(x12), x13(x13), x21(x21), x22(x22), x23(x23), x31(x31), x32(x32), x33(x33) {};

Matrix3::Matrix3(Vector3 v1, Vector3 v2, Vector3 v3) {
    x11 = v1.x;
    x12 = v2.x;
    x13 = v3.x;
    x21 = v1.y;
    x22 = v2.y;
    x23 = v3.y;
    x31 = v1.z;
    x32 = v2.z;
    x33 = v3.z;
}

// Creates rotation matrix from Extrinsic Tait-Bryan angles in rotation order xyz
Matrix3 Matrix3::createEulerRotationMatrix(const double xRotation, const double yRotation, const double zRotation) {
    Matrix3 m;
    m.x11 = std::cos(yRotation) * std::cos(zRotation);
    m.x12 = std::cos(zRotation) * std::sin(yRotation) * std::sin(xRotation) - std::cos(xRotation) * std::sin(zRotation);
    m.x13 = std::cos(xRotation) * std::cos(zRotation) * std::sin(yRotation) + std::sin(xRotation) * std::sin(zRotation);
    m.x21 = std::cos(yRotation) * std::sin(zRotation);
    m.x22 = std::cos(xRotation) * std::cos(zRotation) + std::sin(yRotation) * std::sin(xRotation) * std::sin(zRotation);
    m.x23 = std::cos(xRotation) * std::sin(yRotation) * std::sin(zRotation) - std::cos(zRotation) * std::sin(xRotation);
    m.x31 = -std::sin(yRotation);
    m.x32 = std::cos(yRotation) * std::sin(xRotation);
    m.x33 = std::cos(yRotation) * std::cos(xRotation);
    return m;
}

Matrix3 Matrix3::createSSCrossMatrix(const Vector3 v) {
    return Matrix3(0., -v.z, v.y, v.z, 0., -v.x, -v.y, v.x, 0.);
}

// Creates rotation matrix that rotates (0, 0, 1) to normal
Matrix3 Matrix3::createFromNormal(const Vector3 normal) {
    Vector3 temp(1., 0., 0.);
    if (std::abs(normal.x) > 0.99) {
        temp = Vector3(0., 0., 1.);
    }

    Vector3 tangent = normal.cross(temp).normalized();
    Vector3 binormal = tangent.cross(normal).normalized();
    return Matrix3(tangent, binormal, normal);
}


// Creates rotation matrix that rotates (1, 0, 0) to direction
Matrix3 Matrix3::createFromDirection(const Vector3 direction) {
    Vector3 temp(0., 0., 1.);
    if (std::abs(direction.z) > 0.99) {
        temp = Vector3(0., 1., 0.);
    }

    Vector3 binormal = temp.cross(direction).normalized();
    Vector3 normal = direction.cross(binormal).normalized();
    return Matrix3(direction, binormal, normal);
}

Matrix3& Matrix3::operator*=(const Matrix3 b) {
    x11 = x11 * b.x11 + x12 * b.x21 + x13 * b.x31;
    x12 = x11 * b.x12 + x12 * b.x22 + x13 * b.x32; 
    x13 = x11 * b.x13 + x12 * b.x23 + x13 * b.x33;
    x21 = x21 * b.x11 + x22 * b.x21 + x23 * b.x31;
    x22 = x21 * b.x12 + x22 * b.x22 + x23 * b.x32;
    x23 = x21 * b.x13 + x22 * b.x23 + x23 * b.x33;
    x31 = x31 * b.x11 + x32 * b.x21 + x33 * b.x31;
    x32 = x31 * b.x12 + x32 * b.x22 + x33 * b.x32;
    x33 = x31 * b.x13 + x32 * b.x23 + x33 * b.x33;
    return *this;
}

Matrix3& Matrix3::operator*=(const double b) {
    x11 *= b;
    x12 *= b;
    x13 *= b;
    x21 *= b;
    x22 *= b;
    x23 *= b;
    x31 *= b;
    x32 *= b;
    x33 *= b;
    return *this;
}

Matrix3& Matrix3::operator+=(const Matrix3 b) {
    x11 += b.x11;
    x12 += b.x12;
    x13 += b.x13;
    x21 += b.x21;
    x22 += b.x22;
    x23 += b.x23;
    x31 += b.x31;
    x32 += b.x32;
    x33 += b.x33;
    return *this;
}

Matrix3& Matrix3::operator+=(const double b) {
    x11 += b;
    x12 += b;
    x13 += b;
    x21 += b;
    x22 += b;
    x23 += b;
    x31 += b;
    x32 += b;
    x33 += b;
    return *this;
}
Matrix3 operator*(const Matrix3 a, const Matrix3 b) {
    Matrix3 c = a;
    return c *= b;
}

Matrix3 operator*(const Matrix3 a, const double b) {
    Matrix3 c = a;
    return c *= b;
}

Matrix3 operator+(const Matrix3 a, const Matrix3 b) {
    Matrix3 c = a;
    return c += b;
}

Matrix3 operator+(const Matrix3 a, const double b) {
    Matrix3 c = a;
    return c += b;
}

bool operator==(const Matrix3 a, const Matrix3 b) {
    return (a.x11 == b.x11) && (a.x12 == b.x12) && (a.x13 == b.x13) && (a.x21 == b.x21) && (a.x22 == b.x22) && (a.x23 == b.x23) && (a.x31 == b.x31) && (a.x32 == b.x32) && (a.x33 == b.x33);
}

bool operator!=(const Matrix3 a, const Matrix3 b) {
    return !(a == b);
}