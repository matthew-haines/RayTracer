#include "obj_reader.hpp"
#include "../primitive/triangle.hpp"
#include <fstream>

ComplexPrimitive* ParseOBJFile(std::string filepath, Material* material, Vector3 position, double scale) {
    // only handles faces and vertices for now
    std::vector<Vector3> vertices;
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
            Vector3 vertex(x, y, z);
            vertices.push_back((vertex * scale) + position);
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
            mesh->primitives.push_back(new Triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], material));
        }
    }
    return mesh;
}