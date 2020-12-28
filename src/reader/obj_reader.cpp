#include "obj_reader.hpp"
#include "triangle.hpp"
#include "matrix3.hpp"
#include <fstream>

ComplexPrimitive* parseObjFile(const std::string filepath, const Material material, const Vector3 position, const Vector3 rotation, const double scale, const bool normal) {
    // only handles faces and vertices for now
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector2> textures;
    Matrix3 rotationMatrix = Matrix3::createEulerRotationMatrix(rotation.x, rotation.y, rotation.z);
    ComplexPrimitive* mesh = new ComplexPrimitive;
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == 'v') {
            if (line[1] == 't') {
                std::string::size_type start = 2;
                std::string::size_type offset;
                double x = std::stod(line.substr(start), &offset);
                start += offset;
                double y = std::stod(line.substr(start), &offset);
                Vector2 vector(x, y);
                textures.push_back(vector);
            } else {
                std::string::size_type start = 2;
                std::string::size_type offset;
                double x = std::stod(line.substr(start), &offset);
                start += offset;
                double y = std::stod(line.substr(start), &offset);
                start += offset;
                double z = std::stod(line.substr(start), &offset);
                Vector3 vector(x, y, z);
                if (line[1] == 'n') {
                    normals.push_back(rotationMatrix * vector);
                } else {
                    vertices.push_back((rotationMatrix * vector * scale) + position);
                }
            }
        } else if (line[0] == 'f') {
            int v0, vt0, vn0, v1, vt1, vn1, v2, vt2, vn2;
            bool hasNormals = false;
            bool hasTextures = false;
            std::string::size_type start = 2;
            std::string::size_type offset;
            v0 = std::stoi(line.substr(start), &offset);
            start += offset;
            if (line[start] == '/') {
                if (line[start+1] == '/') {
                    start += 1;
                } else {
                    start += 1;
                    hasTextures = true;
                    vt0 = std::stoi(line.substr(start), &offset);
                    start += offset;
                }
                start += 1;
                hasNormals = true;
                vn0 = std::stoi(line.substr(start), &offset);
                start += offset;
            }
            v1 = std::stoi(line.substr(start), &offset);
            start += offset;
            if (hasNormals) {
                if (!hasTextures) {
                    start += 1;
                } else {
                    start += 1;
                    vt1 = std::stoi(line.substr(start), &offset);
                    start += offset;
                }
                start += 1; 
                vn1 = std::stoi(line.substr(start), &offset);
                start += offset;
            }
            v2 = std::stoi(line.substr(start), &offset);
            start += offset;
            if (hasNormals) {
                if (!hasTextures) {
                    start += 1;
                } else {
                    start += 1;
                    vt2 = std::stoi(line.substr(start), &offset);
                    start += offset;
                }
                start += 1; 
                vn2 = std::stoi(line.substr(start), &offset);
                start += offset;
            }
            if (normal && hasNormals) {
                mesh->primitives.push_back(new Triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], material, true, normals[vn0-1], normals[vn1-1], normals[vn2-1]));
            } else {
                mesh->primitives.push_back(new Triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], material));
            }
        }
    }
    return mesh;
}