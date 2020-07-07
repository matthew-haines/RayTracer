#include "helpers.hpp"

template <typename T>
T mix(T x, T y, double a) {
    return x * (1. - a) + y * a;
}

template <typename T>
T square(T x) {
    return x * x;
}