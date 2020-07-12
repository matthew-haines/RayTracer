#ifndef MATRIX3_HPP
#define MATRIX3_HPP

class Vector3;

class Matrix3 {
    public:
        double x11, x12, x13, x21, x22, x23, x31, x32, x33;
        Matrix3() = default;
        Matrix3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33);
        Matrix3(Vector3 v1, Vector3 v2, Vector3 v3);
        static Matrix3 createEulerRotationMatrix(double xRotation, double yRotation, double zRotation);
        static Matrix3 createSSCrossMatrix(Vector3 v);
        static Matrix3 createFromNormal(Vector3 normal);
        Matrix3(double xRotation, double yRotation, double zRotation);
        Matrix3(Vector3 initial, Vector3 final);
        Matrix3& operator*=(Matrix3 b);
        Matrix3& operator*=(double b);
        Matrix3& operator+=(Matrix3 b);
        Matrix3& operator+=(double b);
};

Matrix3 operator*(Matrix3 a, Matrix3 b);
Matrix3 operator*(Matrix3 a, double b);
Matrix3 operator+(Matrix3 a, Matrix3 b);
Matrix3 operator+(Matrix3 a, double b);
bool operator==(Matrix3 a, Matrix3 b);

#endif