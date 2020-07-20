#include "reader.hpp"
#include "../vector3.hpp"
#include "../material/material.hpp"
#include <fstream>
#include <map>

Vector3 Vector3FromJSON(json j) {
    if (j.size() != 3 || !j.is_array()) {
        throw "Wrong number of parameters for Vector3";
    }
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        if (!it->is_number()) {
            throw "Non-numerical parameter for Vector3";
        }
    }
    return Vector3(j[0].get<double>(), j[1].get<double>(), j[2].get<double>());
}

Material MaterialFromJSON(json j) {
    if ()
}
 
Scene ParseSceneFromFile(std::string filename) {
    std::ifstream f(filename);
    json j;
    f >> j;

    std::map<std::string, Material> materials();
    json materials_json = j["materials"];
    if (!materials_json.is_array()) {
        throw "Bad material list";
    }
    for (json::iterator material = materials_json.begin(); material != materials_json.end(); ++material) {
        std::string name = 
    }
}