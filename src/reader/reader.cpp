#include "reader.hpp"
#include "../material/material.hpp"
#include "../material/bxdf.hpp"
#include "../material/lambertian_brdf.hpp"
#include "../material/perfect_specular_brdf.hpp"
#include "../primitive/primitive.hpp"
#include "../primitive/sphere.hpp"
#include "../primitive/plane.hpp"
#include "../primitive/triangle.hpp"
#include "../primitive/quad.hpp"
#include "../vector3.hpp"
#include "obj_reader.hpp"
#include <fstream>
#include <string>
#include <map>
#include <variant>

void from_json(const json& j, Vector3& v) {
    j.at(0).get_to(v.x);
    j.at(1).get_to(v.y);
    j.at(2).get_to(v.z);
}

Scene ParseSceneFromFile(std::string filename) {
    std::ifstream f(filename);
    json j;
    f >> j;

    std::map<std::string, BxDF*> bxdfs;
    json bxdfs_json = j.at("bxdfs");
    if (!bxdfs_json.is_array()) {
        throw "Bad BxDF list";
    }
    for (json::iterator bxdf_json = bxdfs_json.begin(); bxdf_json != bxdfs_json.end(); ++bxdf_json) {
        std::string name = bxdf_json->at("name").get<std::string>();
        BxDF *bxdf;
        std::string type = bxdf_json->at("type").get<std::string>();
        if (type == "LambertianBRDF") {
            bxdf = new LambertianBRDF(bxdf_json->at("params").at("albedo").get<double>());
        } else if (type == "PerfectSpecularBRDF") {
            bxdf = new PerfectSpecularBRDF();
        } else {
            throw "BxDF doesn't exist";
        }
        bxdfs[name] = bxdf;
    }

    std::map<std::string, Material*> materials;
    json materials_json = j.at("materials");
    if (!materials_json.is_array()) {
        throw "Bad material list";
    }
    for (json::iterator material_json = materials_json.begin(); material_json != materials_json.end(); ++material_json) {
        std::string name = material_json->at("name").get<std::string>();
        Material *material = new Material;
        material->color = material_json->at("color").get<Vector3>();
        material->emission = material_json->at("emission").get<double>();
        material->bxdf = bxdfs[material_json->at("bxdf").get<std::string>()];
        materials[name] = material;
    }

    Scene scene;
    json objects_json = j.at("objects");
    for (json::iterator object_json = objects_json.begin(); object_json != objects_json.end(); ++object_json) {
        std::variant<Primitive*, ComplexPrimitive*> object;
        std::string type = object_json->at("type").get<std::string>();
        if (type == "Sphere") {
            Vector3 center = object_json->at("center").get<Vector3>();
            double radius = object_json->at("radius").get<double>();
            Material *material = materials[object_json->at("material").get<std::string>()];
            object = new Sphere(center, radius, material);
        } else if (type == "Plane") {
            Vector3 normal = object_json->at("normal").get<Vector3>();
            double d = object_json->at("d").get<double>();
            Material *material = materials[object_json->at("material").get<std::string>()];
            object = new Plane(normal.normalized(), d, material);

        } else if (type == "Triangle") {
            Vector3 v0 = object_json->at("v0").get<Vector3>();
            Vector3 v1 = object_json->at("v1").get<Vector3>();
            Vector3 v2 = object_json->at("v2").get<Vector3>();
            Material *material = materials[object_json->at("material").get<std::string>()];
            object = new Triangle(v0, v1, v2, material);
        } else if (type == "Quad") {
            Vector3 v0 = object_json->at("v0").get<Vector3>();
            Vector3 v1 = object_json->at("v1").get<Vector3>();
            Vector3 v2 = object_json->at("v2").get<Vector3>();
            Vector3 v3 = object_json->at("v3").get<Vector3>();
            Material *material = materials[object_json->at("material").get<std::string>()];
            object = new Quad(v0, v1, v2, v3, material);
        } else if (type == "OBJ") {
            std::string filepath = object_json->at("path").get<std::string>();
            Material *material = materials[object_json->at("material").get<std::string>()];
            double scale = object_json->at("scale").get<double>();
            Vector3 position = object_json->at("position").get<Vector3>();
            object = ParseOBJFile(filepath, material, position, scale);
        } else {
            throw "Object type doesn't exist";
        }
        scene.Insert(object);
    }
    return scene;
}