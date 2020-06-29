#include <iostream>
#include <chrono>
#include "../lib/Eigen/Dense"
#include <math.h>

using namespace std;
using namespace std::chrono;

class Vector3 {
    public:
        double x, y, z;
        Vector3(double x, double y, double z): x(x), y(y), z(z) {};
        Vector3 operator+(Vector3 vec) {
            return Vector3(x + vec.x, y + vec.y, z + vec.z);
        };
        Vector3& operator+=(Vector3 vec) {
            x += vec.x;
            y += vec.y;
            z += vec.z;
        };
        Vector3& operator*=(double num) {
            x *= num;
            y *= num;
            z *= num;
        };
        double dot(Vector3 vec) {
            return x * vec.x + y * vec.y + z * vec.z;
        };
        double length() {
            return sqrt(x * x + y * y + z * z);
        };
        void normalize() {
            double magnitude = length();
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
};

int main() {
    double x=1.2, y=4.5, z=0.2, a=5.1, b=7.1232, c=-4.2;
    Vector3 vec1(x, y, z);
    Vector3 vec2(a, b, c);
    Eigen::Vector3d evec1(x, y, z);
    Eigen::Vector3d evec2(a, b, c);

    // Add
    auto start = high_resolution_clock::now();
    Vector3 result = vec1 + vec2;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    Eigen::Vector3d eresult = evec1 + evec2;
    stop = high_resolution_clock::now();
    auto eduration = duration_cast<nanoseconds>(stop - start);

    std::cout << "Adding: " << endl << "Custom: " << duration.count() << endl << "Eigen: " << eduration.count() << endl;

    // Scalar Multiply
    start = high_resolution_clock::now();
    result *= 2.34;
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    eresult *= 2.34;
    stop = high_resolution_clock::now();
    eduration = duration_cast<nanoseconds>(stop - start);

    std::cout << "Scalar multiplying: " << endl << "Custom: " << duration.count() << endl << "Eigen: " << eduration.count() << endl;

    // Dot product
    start = high_resolution_clock::now();
    double norm = vec1.dot(vec2);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    double enorm = evec1.dot(evec2);
    stop = high_resolution_clock::now();
    eduration = duration_cast<nanoseconds>(stop - start);

    std::cout << "Dot product: " << endl << "Custom: " << duration.count() << endl << "Eigen: " << eduration.count() << endl;

    // Normalize
    start = high_resolution_clock::now();
    vec1.normalize();
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    evec1.normalize();
    stop = high_resolution_clock::now();
    eduration = duration_cast<nanoseconds>(stop - start);

    std::cout << "Normalize: " << endl << "Custom: " << duration.count() << endl << "Eigen: " << eduration.count() << endl;
}