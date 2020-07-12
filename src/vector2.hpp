#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
    public:
        double x, y;
        Vector2() = default;
        Vector2(double x, double y);
        Vector2(double x);
        Vector2& operator+=(Vector2 vec);         
        Vector2& operator-=(Vector2 vec);
        Vector2& operator*=(Vector2 vec);
        Vector2& operator/=(Vector2 vec);
        Vector2& operator+=(double a);         
        Vector2& operator-=(double a);
        Vector2& operator*=(double a);
        Vector2& operator/=(double a);
        double dot(Vector2 vec);
        double length();
        void normalize();
        Vector2 normalized();
};

Vector2 operator+(Vector2 a, Vector2 b);         
Vector2 operator-(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 a, Vector2 b);
Vector2 operator/(Vector2 a, Vector2 b);
Vector2 operator+(Vector2 a, double b);         
Vector2 operator-(Vector2 a, double b);
Vector2 operator*(Vector2 a, double b);
Vector2 operator/(Vector2 a, double b);
Vector2 operator-(Vector2& v);
bool operator==(Vector2 a, Vector2 b);

#endif