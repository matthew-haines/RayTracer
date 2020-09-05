#ifndef MATRIX3_HPP
#define MATRIX3_HPP

class Vector3;

class Matrix3 {
    public:
        double x11, x12, x13, x21, x22, x23, x31, x32, x33;
        Matrix3() = default;
        Matrix3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33);
        Matrix3(Vector3 v1, Vector3 v2, Vector3 v3);
        static Matrix3 createEulerRotationMatrix(const double xRotation, const double yRotation, const double zRotation);
        static Matrix3 createSSCrossMatrix(const Vector3 v);
        static Matrix3 createFromNormal(const Vector3 normal);
        static Matrix3 createFromDirection(const Vector3 direction);
        Matrix3& operator*=(const Matrix3 b);
        Matrix3& operator*=(const double b);
        Matrix3& operator+=(const Matrix3 b);
        Matrix3& operator+=(const double b);
};

Matrix3 operator*(const Matrix3 a, const Matrix3 b);
Matrix3 operator*(const Matrix3 a, const double b);
Matrix3 operator+(const Matrix3 a, const Matrix3 b);
Matrix3 operator+(const Matrix3 a, const double b);
bool operator==(const Matrix3 a, const Matrix3 b);
bool operator!=(const Matrix3 a, const Matrix3 b);

#endif