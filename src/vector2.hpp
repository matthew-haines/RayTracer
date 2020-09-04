#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
    public:
        double x, y;
        Vector2() = default;
        Vector2(double x, double y);
        Vector2(double x);
        Vector2& operator+=(const Vector2 vec);         
        Vector2& operator-=(const Vector2 vec);
        Vector2& operator*=(const Vector2 vec);
        Vector2& operator/=(const Vector2 vec);
        Vector2& operator+=(const double a);         
        Vector2& operator-=(const double a);
        Vector2& operator*=(const double a);
        Vector2& operator/=(const double a);
        double dot(const Vector2 vec) const;
        double length() const;
        void normalize();
        Vector2 normalized() const;
};

Vector2 operator+(const Vector2 a, const Vector2 b);         
Vector2 operator-(const Vector2 a, const Vector2 b);
Vector2 operator*(const Vector2 a, const Vector2 b);
Vector2 operator/(const Vector2 a, const Vector2 b);
Vector2 operator+(const Vector2 a, const double b);         
Vector2 operator-(const Vector2 a, const double b);
Vector2 operator*(const Vector2 a, const double b);
Vector2 operator/(const Vector2 a, const double b);
Vector2 operator-(const Vector2& v);
bool operator==(const Vector2 a, const Vector2 b);
bool operator!=(const Vector2 a, const Vector2 b);

#endif