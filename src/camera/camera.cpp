#include "camera.hpp"
#include "../helpers.hpp"
#include "../../lib/lodepng/lodepng.h"
#include <cmath>
#include <iostream>

Camera::Camera(std::size_t width, std::size_t height, Vector3 direction, Vector3 position): width(width), height(height), direction(direction), position(position) {
    result = std::vector<Vector3>(width * height);
    rotation = Matrix3::createEulerRotationMatrix(0.0, std::atan(direction.z / Vector3(direction.x, direction.y, 0.0).length()), std::atan(direction.y / direction.x));
}

void Camera::BuildQueue() {
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            queue.push(std::make_pair(PixelFunction(row, column), &result[row * width + column]));
        }
    }
}

std::function<Ray()> Camera::Next(Vector3** location) {
    std::unique_lock<std::mutex> lock(mutex);
    if (queue.size() != 0) {
        auto pair = queue.front();
        queue.pop();
        lock.unlock(); 
        *location = pair.second;
        return pair.first;
    } else {
        lock.unlock();
        *location = nullptr;
        return NULL;
    }
}

void Camera::Write(std::string path, double gamma, std::size_t threads) {
    std::vector<unsigned char> buffer(result.size() * 4);

    std::function<void(int)> charConv = [&buffer, this, gamma](int index) {
        int baseIndex = index * 4;
        buffer[baseIndex] = ColorToChar(std::pow(result[index].x, 1/gamma));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].y, 1/gamma));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].z, 1/gamma));
        buffer[++baseIndex] = 255;
    };
    
    ParallelizeLoop(threads, charConv, result.size());

    unsigned error = lodepng::encode(path, buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}