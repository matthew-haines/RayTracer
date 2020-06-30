#include "color.hpp"
#include "perspective_camera.hpp"
#include "vector3.hpp"
#include "lodepng.h"
#include <math.h>
#include <iostream>
#include <functional>

PerspectiveCamera::PerspectiveCamera(int width, int height, double fov, Vector3 direction): width(width), height(height) {
    rays = new Ray*[height];
    double maxWidth = 2 * sqrt(1 / pow(cos(fov/2), 2) - 1);
    double stepSize = maxWidth / width;
    double maxHeight = stepSize * height;
    for (int row = 0; row < height; row++) {
        rays[row] = new Ray[width];
        for (int column = 0; column < width; column++) {
            Ray ray = {Vector3(0.0, 0.0, 0.0), Vector3(1.0, (stepSize - maxWidth)/2 + column * stepSize, (maxHeight-stepSize)/2 - row * stepSize)};
            rays[row][column] = ray;
        }
    }
}

void PerspectiveCamera::generate(std::function<Color(Ray, int)> raytrace) {
    colors = new Color*[height];
    for (int row = 0; row < height; row ++) {
        colors[row] = new Color[width];
        for (int column = 0; column < width; column++) {
            colors[row][column] = raytrace(rays[row][column], 4); 
        }
    }
}

void PerspectiveCamera::write(char *filename) {
    std::vector<unsigned char> buffer(width * height * 4);
    for (int row = 0; row < height; row ++) {
        for (int column = 0; column < width; column++) {
            int baseIndex = width * row + column;
            Color color = colors[row][column];
            buffer[baseIndex] = ColorToChar(color.r);
            buffer[baseIndex+1] = ColorToChar(color.g);
            buffer[baseIndex+2] = ColorToChar(color.b);
            buffer[baseIndex+3] = 255;
        }
    }
    unsigned error = lodepng::encode(filename, buffer, width, height);
    if (!error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}