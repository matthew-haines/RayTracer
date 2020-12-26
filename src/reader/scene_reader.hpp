#ifndef SCENE_READER_HPP
#define SCENE_READER_HPP

#include "scene.hpp"
#include "json.hpp"
#include <string>

using json = nlohmann::json;

Scene parseScene(const json j);

#endif