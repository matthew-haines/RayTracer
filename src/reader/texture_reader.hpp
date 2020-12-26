#ifndef TEXTURE_READER_HPP
#define TEXTURE_READER_HPP

#include "texture.hpp"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

Texture* parseTexture(const json j);

#endif