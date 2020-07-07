#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include "matrix3.hpp"

class Vector3 {
    public:
        double x, y, z;
        Vector3() = default;
        Vector3(double x, double y, double z);
        Vector3(double x);
        Vector3& operator+=(Vector3 vec);         
        Vector3& operator-=(Vector3 vec);
        Vector3& operator*=(Vector3 vec);
        Vector3& operator/=(Vector3 vec);
        Vector3& operator+=(double a);         
        Vector3& operator-=(double a);
        Vector3& operator*=(double a);
        Vector3& operator/=(double a);
        double dot(Vector3 vec);
        Vector3 cross(Vector3 vec);
        double length();
        void normalize();
        Vector3 normalized();
};

Vector3 operator+(Vector3 a, Vector3 b);         
Vector3 operator-(Vector3 a, Vector3 b);
Vector3 operator*(Vector3 a, Vector3 b);
Vector3 operator/(Vector3 a, Vector3 b);
Vector3 operator+(Vector3 a, double b);         
Vector3 operator-(Vector3 a, double b);
Vector3 operator*(Vector3 a, double b);
Vector3 operator/(Vector3 a, double b);
bool operator==(Vector3 a, Vector3 b);
Vector3 operator*(Matrix3 a, Vector3 b);

Vector3 mix(Vector3 x, Vector3 y, double a);
char ColorToChar(double color);

#endif