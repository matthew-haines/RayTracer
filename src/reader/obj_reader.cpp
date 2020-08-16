#include "obj_reader.hpp"
#include "../primitive/triangle.hpp"
#include "../matrix3.hpp"
#include <fstream>

ComplexPrimitive* ParseOBJFile(std::string filepath, Material* material, Vector3 position, Vector3 rotation, double scale, bool normal) {
    // only handles faces and vertices for now
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    Matrix3 rotationMatrix = Matrix3::createEulerRotationMatrix(rotation.x, rotation.y, rotation.z);
    ComplexPrimitive* mesh = new ComplexPrimitive;
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == 'v') {
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
        } else if (line[0] == 'f') {
            std::string::size_type start = 2;
            std::string::size_type offset;
            int v0 = std::stoi(line.substr(start), &offset);
            start += offset + 2;
            int vn0 = std::stoi(line.substr(start), &offset);
            start += offset;
            int v1 = std::stoi(line.substr(start), &offset);
            start += offset + 2;
            int vn1 = std::stoi(line.substr(start), &offset);
            start += offset;
            int v2 = std::stoi(line.substr(start), &offset);
            start += offset + 2;
            int vn2 = std::stoi(line.substr(start), &offset);
            if (normal) {
                mesh->primitives.push_back(new Triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], material, true, normals[vn0-1], normals[vn1-1], normals[vn2-1]));
            } else {
                mesh->primitives.push_back(new Triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], material));
            }
        }
    }
    return mesh;
}