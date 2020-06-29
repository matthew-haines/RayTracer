#include <assert.h>
#include "../src/vector3.hpp"

void test_dot() {
    Vector3 vec1(1.0, 0.0, 0.0);
    Vector3 vec2(0.0, 1.0, 0.0);
    assert(vec1.dot(vec2) == 0.0);
}

void test_cross() {
    Vector3 vec1(1.0, 0.0, 0.0);
    Vector3 vec2(0.0, 1.0, 0.0);
    assert(vec1.cross(vec2) == Vector3(0.0, 0.0, 1.0));
}

int main() {
    test_dot();
    test_cross();
}