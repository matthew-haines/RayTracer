#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "matrix3.hpp"
#include "../lib/json/json.hpp"

class Vector3 {
    public:
        double x, y, z;
        Vector3() = default;
        Vector3(double x, double y, double z);
        Vector3(double x);
        Vector3& operator+=(const Vector3 vec);         
        Vector3& operator-=(const Vector3 vec);
        Vector3& operator*=(const Vector3 vec);
        Vector3& operator/=(const Vector3 vec);
        Vector3& operator+=(const double a);         
        Vector3& operator-=(const double a);
        Vector3& operator*=(const double a);
        Vector3& operator/=(const double a);
        double& operator[](const int index);
        double dot(const Vector3 vec) const;
        Vector3 cross(const Vector3 vec) const;
        double length() const;
        double max() const;
        double min() const;
        void normalize();
        Vector3 normalized() const;
        static Vector3 max(const Vector3 a, const Vector3 b);
        static Vector3 min(const Vector3 a, const Vector3 b);
};

Vector3 operator+(const Vector3 a, const Vector3 b);         
Vector3 operator-(const Vector3 a, const Vector3 b);
Vector3 operator*(const Vector3 a, const Vector3 b);
Vector3 operator/(const Vector3 a, const Vector3 b);
Vector3 operator+(const Vector3 a, const double b);         
Vector3 operator-(const Vector3 a, const double b);
Vector3 operator*(const Vector3 a, const double b);
Vector3 operator/(const Vector3 a, const double b);
Vector3 operator-(const Vector3& v);
bool operator==(const Vector3 a, const Vector3 b);
bool operator!=(const Vector3 a, const Vector3 b);
Vector3 operator*(const Matrix3 a, const Vector3 b);

Vector3 sphericalToCartesian(const Vector3 vec);

Vector3 cartesianToSpherical(const Vector3 vec);

void from_json(const nlohmann::json& j, Vector3& v);

#endif