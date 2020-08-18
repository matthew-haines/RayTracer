#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include "matrix3.hpp"
#include "immintrin.h"

union SIMDData {
    __m256d d4;
    double d[4];
};

class Vector3 {
    public:
        SIMDData data;
        Vector3() = default;
        Vector3(double _x, double _y, double _z);
        Vector3(double _x);
        Vector3(__m256d dat);
        double x();
        double y();
        double z();
        Vector3& operator+=(Vector3 vec);         
        Vector3& operator-=(Vector3 vec);
        Vector3& operator*=(Vector3 vec);
        Vector3& operator/=(Vector3 vec);
         Vector3& operator+=(double a);         
        Vector3& operator-=(double a);
        Vector3& operator*=(double a);
        Vector3& operator/=(double a);
        double& operator[](int index);
        double dot(Vector3 vec);
        Vector3 cross(Vector3 vec);
        double length();
        double max();
        double min();
        void normalize();
        Vector3 normalized();
        static Vector3 max(Vector3 a, Vector3 b);
        static Vector3 min(Vector3 a, Vector3 b);
};

Vector3 operator+(Vector3 a, Vector3 b);         
Vector3 operator-(Vector3 a, Vector3 b);
Vector3 operator*(Vector3 a, Vector3 b);
Vector3 operator/(Vector3 a, Vector3 b);
Vector3 operator+(Vector3 a, double b);         
Vector3 operator-(Vector3 a, double b);
Vector3 operator*(Vector3 a, double b);
Vector3 operator/(Vector3 a, double b);
Vector3 operator-(Vector3& v);
bool operator==(Vector3 a, Vector3 b);
Vector3 operator*(Matrix3 a, Vector3 b);
Vector3 SphericalToCartesian(Vector3 vec);
Vector3 CartesianToSpherical(Vector3 vec);

#endif