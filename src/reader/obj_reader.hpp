#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP
#include "../primitive/complex_primitive.hpp"
#include "../material/material.hpp"
#include <string>

ComplexPrimitive* ParseOBJFile(std::string filepath, Material* material, Vector3 position = Vector3(0.), double scale = 1.);

#endif