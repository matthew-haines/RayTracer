#include "texture_reader.hpp"
#include "../helpers.hpp"
#include <iostream>
#include <stdexcept>

Texture parseTextureFile(const std::string filepath) {
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, filepath);
    if (error) {
        std::cout << "Decoder Error on \"" << filepath << "\"." << error << ": " << lodepng_error_text(error) << std::endl;
        throw std::runtime_error("Decoder Error");
    }
    auto colors = new std::vector<Vector3>(width * height);
    for (std::size_t i = 0; i < width * height; i++) {
        std::size_t index = i * 4;
        Vector3 color(charToColor(image[index++]), colorToChar(image[index++]), colorToChar(image[index++]));
        colors->at(i) = color;
    }
    return Texture(colors, width, height);
}