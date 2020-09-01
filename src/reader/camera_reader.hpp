#ifndef CAMERA_READER_HPP
#define CAMERA_READER_HPP
#include "../camera/camera.hpp"
#include "../../lib/json/json.hpp"
#include <string>

using json = nlohmann::json;

Camera* parseCamera(json j, std::size_t width, std::size_t height);

#endif