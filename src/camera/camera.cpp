#include "camera.hpp"
#include "../helpers.hpp"
#include "../../lib/lodepng/lodepng.h"
#include <cmath>
#include <iostream>

Camera::Camera(const std::size_t width, const std::size_t height, const Vector3 direction, const Vector3 position): direction(direction), position(position), width(width), height(height)  {
    result = std::vector<Vector3>(width * height);
    rotation = Matrix3::createEulerRotationMatrix(0.0, std::atan(direction.z / Vector3(direction.x, direction.y, 0.0).length()), std::atan(direction.y / direction.x));
}

void Camera::buildQueue() {
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            queue.push(std::make_pair(getPixelFunction(row, column), &result[row * width + column]));
        }
    }
}

std::function<Ray()> Camera::next(Vector3** location) {
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

void Camera::write(const std::string path, const double gamma, const std::size_t threads) const {
    std::vector<unsigned char> buffer(result.size() * 4);

    std::function<void(int)> charConv = [&buffer, this, gamma](int index) {
        int baseIndex = index * 4;
        buffer[baseIndex] = colorToChar(std::pow(result[index].x, 1/gamma));
        buffer[++baseIndex] = colorToChar(std::pow(result[index].y, 1/gamma));
        buffer[++baseIndex] = colorToChar(std::pow(result[index].z, 1/gamma));
        buffer[++baseIndex] = 255;
    };
    
    parallelizeLoop(threads, charConv, result.size());

    unsigned error = lodepng::encode(path, buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}