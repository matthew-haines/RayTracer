#ifndef MATRIX3_HPP
#define MATRIX3_HPP

class Matrix3 {
    public:
        double x11, x12, x13, x21, x22, x23, x31, x32, x33;
        Matrix3() = default;
        Matrix3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33);
        Matrix3(double xRotation, double yRotation, double zRotation);
        Matrix3& operator*=(Matrix3 b);
};

Matrix3 operator*(Matrix3 a, Matrix3 b);
bool operator==(Matrix3 a, Matrix3 b);

#endif