#include "texture_reader.hpp"
#include "helpers.hpp"
#include "lodepng.h"
#include <iostream>
#include <stdexcept>

Texture* parseTexture(const json j) {
    std::string type = j.at("type");
    if (type == "ImageTexture") {
        std::string filepath = j.at("path");
        std::vector<unsigned char> image;
        unsigned int width, height;
        unsigned int error = lodepng::decode(image, width, height, filepath);
        if (error) {
            std::cout << "Decoder Error on \"" << filepath << "\"." << error << ": " << lodepng_error_text(error) << std::endl;
            throw std::runtime_error("Image Decoder Error");
        }
        auto colors = new std::vector<Vector3>(width * height);
        for (std::size_t i = 0; i < width * height; i++) {
            std::size_t index = i * 4;
            Vector3 color(charToColor(image[index]), charToColor(image[index+1]), charToColor(image[index+2]));
            colors->at(i) = color;
        }
        return new ImageTexture(colors, width, height);
    } else if (type == "CheckerboardTexture") {
        Vector3 colorA = j.contains("colorA") ? j["colorA"].get<Vector3>() : Vector3(0);
        Vector3 colorB = j.contains("colorB") ? j["colorB"].get<Vector3>() : Vector3(1);
        return new CheckerboardTexture(colorA, colorB);
    } else if (type == "ConstantTexture") {
        Vector3 color = j.contains("color") ? j["color"].get<Vector3>() : Vector3(1);
        return new ConstantTexture(color);
    } else {
        throw std::runtime_error("Texture type doesn't exist");
    }
}