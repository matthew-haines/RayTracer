#ifndef MATRIX3_HPP
#define MATRIX3_HPP
#include "vector3.hpp"

class Matrix3 {
    public:
        Vector3 r1, r2, r3;
        Matrix3(Vector3 r1, Vector3 r2, Vector3 r3);
};

#endif