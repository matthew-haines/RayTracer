#ifndef VECTOR3_HPP
#define VECTOR3_HPP

class Vector3 {
    public:
        double x, y, z;
        Vector3() = default;
        Vector3(double x, double y, double z): x(x), y(y), z(z) {};
        Vector3 operator+(Vector3 vec);         
        Vector3 operator-(Vector3 vec);
        Vector3 operator*(Vector3 vec);
        Vector3 operator/(Vector3 vec);
        Vector3& operator+=(Vector3 vec);         
        Vector3& operator-=(Vector3 vec);
        Vector3& operator*=(Vector3 vec);
        Vector3& operator/=(Vector3 vec);
        Vector3 operator+(double a);         
        Vector3 operator-(double a);
        Vector3 operator*(double a);
        Vector3 operator/(double a);
        Vector3& operator+=(double a);         
        Vector3& operator-=(double a);
        Vector3& operator*=(double a);
        Vector3& operator/=(double a);
        bool operator==(Vector3 vec);
        double dot(Vector3 vec);
        Vector3 cross(Vector3 vec);
        double length();
        void normalize();
        Vector3 normalized();
};

#endif