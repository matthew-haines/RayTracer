#ifndef READER_HPP
#define READER_HPP
#include "../scene.hpp"
#include "../../lib/json/json.hpp"

using json = nlohmann::json;

Scene ParseSceneFromFile(std::string filename);

#endif