#include "camera.hpp"
#include "../helpers.hpp"
#include "../../lib/lodepng/lodepng.h"
#include <cmath>
#include <iostream>

Camera::Camera(std::size_t width, std::size_t height, Vector3 position, Vector3 direction): width(width), height(height), direction(direction), position(position) {
    result = std::vector<Vector3>(width * height);
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            queue.push(std::make_pair(PixelFunction(row, column), &(result[row * width + column])));
        }
    }

    rotation = Matrix3::createEulerRotationMatrix(0.0, std::atan(direction.z / Vector3(direction.x, direction.y, 0.0).length()), std::atan(direction.y / direction.x));
}

std::function<Ray()> Camera::Next(Vector3* location) {
    std::unique_lock<std::mutex> lock(mutex);
    if (queue.size() != 0) {
        auto result = queue.front();
        queue.pop();
        lock.unlock(); 
        location = result.second;
        return result.first;
    } else {
        lock.unlock();
        location = nullptr;
        return NULL;
    }
}

void Camera::Write(std::string path, double gamma, std::size_t threads) {
    std::vector<unsigned char> buffer(result.size());

    std::function<void(int)> charConv = [&buffer, this](int index) {
        int baseIndex = index * 4;
        buffer[baseIndex] = ColorToChar(std::pow(result[index].x, 1/2.2));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].y, 1/2.2));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].z, 1/2.2));
        buffer[++baseIndex] = 255;
    };
    
    ParallelizeLoop(threads, charConv, result.size());

    unsigned error = lodepng::encode(path, buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}