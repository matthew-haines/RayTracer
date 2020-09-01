#ifndef SCENE_READER_HPP
#define SCENE_READER_HPP

#include "../scene.hpp"
#include "../../lib/json/json.hpp"
#include <string>

using json = nlohmann::json;

Scene parseScene(json j);

#endif