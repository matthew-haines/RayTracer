#include "matrix3.hpp"
#include "math.h"

Matrix3::Matrix3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33) : x11(x11), x12(x12), x13(x13), x21(x21), x22(x22), x23(x23), x31(x31), x32(x32), x33(x33) {};

Matrix3::Matrix3(double xRotation, double yRotation, double zRotation) {
    // Extrinsic Tait-Bryan angles in rotation order xyz
    x11 = cos(yRotation) * cos(zRotation);
    x12 = cos(zRotation) * sin(yRotation) * sin(xRotation) - cos(xRotation) * sin(zRotation);
    x13 = cos(xRotation) * cos(zRotation) * sin(yRotation) + sin(xRotation) * sin(zRotation);
    x21 = cos(yRotation) * sin(zRotation);
    x22 = cos(xRotation) * cos(zRotation) + sin(yRotation) * sin(xRotation) * sin(zRotation);
    x23 = cos(xRotation) * sin(yRotation) * sin(zRotation) - cos(zRotation) * sin(xRotation);
    x31 = -sin(yRotation);
    x32 = cos(yRotation) * sin(xRotation);
    x33 = cos(yRotation) * cos(xRotation);
}

Matrix3& Matrix3::operator*=(Matrix3 b) {
    x11 = x11 * b.x11 + x12 * b.x21 + x13 * b.x31;
    x12 = x11 * b.x12 + x12 * b.x22 + x13 * b.x32; 
    x13 = x11 * b.x13 + x12 * b.x23 + x13 * b.x33;
    x21 = x21 * b.x11 + x22 * b.x21 + x23 * b.x31;
    x22 = x21 * b.x12 + x22 * b.x22 + x23 * b.x32;
    x23 = x21 * b.x13 + x22 * b.x23 + x23 * b.x33;
    x31 = x31 * b.x11 + x32 * b.x21 + x33 * b.x31;
    x32 = x31 * b.x12 + x32 * b.x22 + x33 * b.x32;
    x33 = x31 * b.x13 + x32 * b.x23 + x33 * b.x33;
}

Matrix3 operator*(Matrix3 a, Matrix3 b) {
    Matrix3 c = a;
    return a *= b;
}

bool operator==(Matrix3 a, Matrix3 b) {
    return (a.x11 == b.x11) && (a.x12 == b.x12) && (a.x13 == b.x13) && (a.x21 == b.x21) && (a.x22 == b.x22) && (a.x23 == b.x23) && (a.x31 == b.x31) && (a.x32 == b.x32) && (a.x33 == b.x33);
}