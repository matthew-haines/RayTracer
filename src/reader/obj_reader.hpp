#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include "complex_primitive.hpp"
#include "material.hpp"
#include <string>

ComplexPrimitive* parseObjFile(const std::string filepath, Material* const material, const Vector3 position = Vector3(0.), const Vector3 rotation = Vector3(0.), const double scale = 1., const bool normal=false);

#endif