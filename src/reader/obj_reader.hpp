#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP
#include "../primitive/complex_primitive.hpp"
#include "../material/material.hpp"
#include <string>

ComplexPrimitive* parseObjFile(std::string filepath, Material* material, Vector3 position = Vector3(0.), Vector3 rotation = Vector3(0.), double scale = 1., bool normal=false);

#endif