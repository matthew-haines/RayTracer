#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include "complex_primitive.hpp"
#include "material.hpp"
#include <string>

// Bespoke OBJ file reader. Translates into a mesh of triangles, includes vertex normals and vertices.
// TODO: Add support for optional texture parsing.
ComplexPrimitive* parseObjFile(const std::string filepath, const Material material, const Vector3 position = Vector3(0.), const Vector3 rotation = Vector3(0.), const double scale = 1., const bool normal=false);

#endif