#include "scene_reader.hpp"
#include "lambertian_brdf.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include "fresnel_specular_bsdf.hpp"
#include "phong_brdf.hpp"
#include "microfacet_bsdf.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "triangle.hpp"
#include "quad.hpp"
#include "polygon.hpp"
#include "obj_reader.hpp"
#include "texture_reader.hpp"
#include <map>
#include <variant>
#include <iostream>
#include <stdexcept>

Scene parseScene(const json j) {
    std::map<std::string, BxDF*> bxdfs;
    json bxdfs_json = j.at("bxdfs");
    if (!bxdfs_json.is_array()) {
        throw std::runtime_error("Bad BxDF list");
    }
    for (json::iterator bxdf_json = bxdfs_json.begin(); bxdf_json != bxdfs_json.end(); ++bxdf_json) {
        std::string name = bxdf_json->at("name").get<std::string>();
        BxDF *bxdf;
        std::string type = bxdf_json->at("type").get<std::string>();
        if (type == "LambertianBRDF") {
            auto params = bxdf_json->at("params");
            bxdf = new LambertianBRDF(params.at("albedo").get<double>());
        } else if (type == "SpecularReflectBRDF") {
            bxdf = new SpecularReflectBRDF();
        } else if (type == "SpecularRefractBTDF") {
            auto params = bxdf_json->at("params");
            bxdf = new SpecularRefractBTDF(params.at("refractionIndex").get<double>());
        } else if (type == "FresnelSpecularBSDF") {
            auto params = bxdf_json->at("params");
            bxdf = new FresnelSpecularBSDF(params.at("refractionIndex").get<double>());
        } else if (type == "PhongBRDF") {
            auto params = bxdf_json->at("params");
            bxdf = new PhongBRDF(params.at("kd").get<double>(), params.at("ks").get<double>(), params.at("n").get<double>());
        } else if (type == "MicrofacetBSDF") {
            auto params = bxdf_json->at("params");
            double refractionIndex = params.contains("refractionIndex") ? params["refractionIndex"].get<double>() : 2;
            MicrofacetDistribution* distribution;
            {
                auto distribution_json = params.at("distribution");
                double alpha = distribution_json.at("alpha").get<double>();
                std::string distributionName = distribution_json.at("type").get<std::string>();
                if (distributionName == "Beckmann") {
                    distribution = new BeckmannDistribution(alpha);
                } else if (distributionName == "Phong") {
                    distribution = new PhongDistribution(alpha);
                } else if (distributionName == "GGX") {
                    distribution = new GGXDistribution(alpha);
                } else {
                    throw std::runtime_error("Distribution type doesn't exist");
                }
            }
            Fresnel* fresnel;
            {
                auto fresnel_json = params.at("fresnel");
                std::string fresnelName = fresnel_json.at("type").get<std::string>();
                if (fresnelName == "Dielectric") {
                    fresnel = new DielectricFresnel();
                } else if (fresnelName == "Reflectance") {
                    fresnel = new ReflectanceFresnel();
                } else if (fresnelName == "Transmittance") {
                    fresnel = new TransmittanceFresnel();
                } else if (fresnelName == "Fixed") {
                    double ratio = fresnel_json.at("ratio").get<double>();
                    fresnel = new FixedFresnel(ratio);
                } else {
                    throw std::runtime_error("Fresnel type doesn't exist");
                }
            }
            bxdf = new MicrofacetBSDF(refractionIndex, fresnel, distribution);
        } else {
            throw std::runtime_error("BxDF doesn't exist");
        }
        bxdfs[name] = bxdf;
    }

    std::map<std::string, Texture*> textures;
    json textures_json = j.at("textures");
    if (!textures_json.is_array()) {
        throw std::runtime_error("Bad texture list");
    }
    for (json::iterator texture_json = textures_json.begin(); texture_json != textures_json.end(); ++texture_json) {
        try {
            std::string name = texture_json->at("name").get<std::string>();
            textures[name] = parseTexture(texture_json.value());
        } catch (const char* error) {
            throw std::runtime_error("Error parsing texture");
        }
    }

    std::map<std::string, Material> materials;
    json materials_json = j.at("materials");
    if (!materials_json.is_array()) {
        throw std::runtime_error("Bad material list");
    }
    for (json::iterator material_json = materials_json.begin(); material_json != materials_json.end(); ++material_json) {
        try {
            std::string name = material_json->at("name").get<std::string>();
            Material material;
            material.emission = material_json->at("emission").get<double>();
            material.bxdf = bxdfs[material_json->at("bxdf").get<std::string>()];
            materials[name] = material;
        } catch (const char* error) {
            throw std::runtime_error("Error parsing material");
        }
    }

    Scene scene;
    json objects_json = j.at("objects");
    for (json::iterator object_json = objects_json.begin(); object_json != objects_json.end(); ++object_json) {
        std::variant<Primitive*, ComplexPrimitive*> object;
        std::string type = object_json->at("type").get<std::string>();
        Material material = materials.at(object_json->at("material").get<std::string>());

        json texture_map_json = object_json->at("textureMap");
        Texture* texture = textures[texture_map_json.at("texture").get<std::string>()];
        std::string texture_map_type = texture_map_json.contains("type") ? texture_map_json.at("type").get<std::string>() : "simple";

        TextureMap* texture_map;
        if (texture_map_type == "simple") {
            Vector2 scale = texture_map_json.contains("scale") ? texture_map_json.at("scale").get<Vector2>() : Vector2(1);
            Vector2 offset = texture_map_json.contains("offset") ? texture_map_json.at("offset").get<Vector2>() : Vector2(0);
            texture_map = new SimpleTextureMap(scale, offset, texture);
        } else {
            // Temp default
            Vector2 scale = texture_map_json.contains("scale") ? texture_map_json.at("scale").get<Vector2>() : Vector2(1);
            Vector2 offset = texture_map_json.contains("offset") ? texture_map_json.at("offset").get<Vector2>() : Vector2(0);
            texture_map = new SimpleTextureMap(scale, offset, texture);
        }
        material.textureMap = texture_map;

        if (type == "Sphere") {
            Vector3 center = object_json->at("center").get<Vector3>();
            double radius = object_json->at("radius").get<double>();
            object = new Sphere(center, radius, material);
        } else if (type == "Plane") {
            Vector3 normal = object_json->at("normal").get<Vector3>();
            double d = object_json->at("d").get<double>();
            object = new Plane(normal.normalized(), d, material);
        } else if (type == "Triangle") {
            Vector3 v0 = object_json->at("v0").get<Vector3>();
            Vector3 v1 = object_json->at("v1").get<Vector3>();
            Vector3 v2 = object_json->at("v2").get<Vector3>();
            object = new Triangle(v0, v1, v2, material);
        } else if (type == "Quad") {
            Vector3 v0 = object_json->at("v0").get<Vector3>();
            Vector3 v1 = object_json->at("v1").get<Vector3>();
            Vector3 v2 = object_json->at("v2").get<Vector3>();
            Vector3 v3 = object_json->at("v3").get<Vector3>();
            object = new Quad(v0, v1, v2, v3, material);
        } else if (type == "Polygon") {
            json points_json = object_json->at("points");
            std::vector<Vector3> points;
            for (int i = 0; i < points_json.size(); ++i) {
                points.push_back(points_json[i].get<Vector3>());
            }
            object = new Polygon(points, material);
        } else if (type == "OBJ") {
            std::string filepath = object_json->at("path").get<std::string>();
            double scale = object_json->at("scale").get<double>();
            Vector3 position = object_json->at("position").get<Vector3>();
            Vector3 rotation = object_json->at("rotation").get<Vector3>();
            object = parseObjFile(filepath, material, position, rotation, scale, true);
        } else {
            throw std::runtime_error("Object type doesn't exist");
        }
        scene.insert(object);
    }
    return scene;
}