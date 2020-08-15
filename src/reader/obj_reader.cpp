#include "obj_reader.hpp"
#include "../primitive/triangle.hpp"
#include <fstream>

ComplexPrimitive* ParseOBJFile(std::string filepath, Material* material) {
    // only handles faces and vertices for now
    std::vector<Vector3> vertices;
    ComplexPrimitive* mesh = new ComplexPrimitive;
    std::ifstream file(filepath);
    for (std::string line; std::getline(file, line); ) {
        if (line[0] == 'v') {
            std::string::size_type start = 2;
            std::string::size_type offset;
            double x = std::stod(line.substr(start), &offset);
            start += offset;
            double y = std::stod(line.substr(start), &offset);
            start += offset;
            double z = std::stod(line.substr(start), &offset);
            vertices.emplace_back(x, y, z);
            break;
        } else if (line[0] == 'f') {
            std::string::size_type start = 2;
            std::string::size_type offset;
            int v0 = std::stoi(line.substr(start), &offset);
            start += offset + 2;
            int vn = std::stoi(line.substr(start), &offset);
            start += offset;
            int v1 = std::stoi(line.substr(start), &offset);
            start += offset + 2;
            vn = std::stoi(line.substr(start), &offset);
            start += offset;
            int v2 = std::stoi(line.substr(start), &offset);
            mesh->primitives.push_back(new Triangle(v0, v1, v2, material));
            break;
        }
    }
    return mesh;
}