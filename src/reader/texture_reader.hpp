#ifndef TEXTURE_READER_HPP
#define TEXTURE_READER_HPP

#include "../../lib/lodepng/lodepng.h"
#include "../material/texture.hpp"
#include <vector>

Texture parseTextureFile(const std::string filepath);

#endif