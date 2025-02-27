#ifndef CAMERA_READER_HPP
#define CAMERA_READER_HPP

#include "camera.hpp"
#include "json.hpp"
#include <string>

using json = nlohmann::json;

Camera* parseCamera(const json j, const std::size_t width, const std::size_t height, const int samples);

#endif