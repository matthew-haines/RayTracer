#include "cameras.hpp"
#include "vector3.hpp"
#include "matrix3.hpp"
#include "ray.hpp"
#include <math.h>
#include <vector>

std::vector<Ray> PerspectiveCamera(int width, int height, double fov, Vector3 direction) {
    double zRotation = atan(direction.y / direction.x);
    double yRotation = atan(direction.z / Vector3(direction.x, direction.y, 0.0).length());
    Matrix3 rotation(0.0, yRotation, zRotation);
    std::vector<Ray> rays(height * width);    
    double maxWidth = 2 * sqrt(1 / pow(cos(fov/2), 2) - 1);
    double stepSize = maxWidth / width;
    double maxHeight = stepSize * height;
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            Ray ray = {Vector3(0.0, 0.0, 0.0), rotation * Vector3(1.0, (maxWidth - stepSize) / 2 - column * stepSize, (maxHeight - stepSize) / 2 - row * stepSize).normalized()};
            rays[row * width + column] = ray;
        }
    }
    return rays;
}