#include "camera_reader.hpp"
#include "perspective_camera.hpp"
#include "orthographic_camera.hpp"
#include <stdexcept>

Camera* parseCamera(const json j, const std::size_t width, const std::size_t height, const int samples) {
    json camera_json = j.at("camera");
    std::string type = camera_json.at("type").get<std::string>();
    Camera* camera;
    if (type == "PerspectiveCamera") {
        double fov = camera_json.contains("fov") ? camera_json["fov"].get<double>() : M_PI_2;
        bool jitter = camera_json.contains("jitter") ? camera_json["jitter"].get<bool>() : true;
        double focalDistance = camera_json.contains("focalDistance") ? camera_json["focalDistance"].get<double>() : 1;
        double lenseRadius = camera_json.contains("lenseRadius") ? camera_json["lenseRadius"].get<double>() : 0;
        Vector3 direction = camera_json.contains("direction") ? camera_json["direction"].get<Vector3>() : Vector3(1, 0, 0);
        direction.normalize();
        Vector3 position = camera_json.contains("position") ? camera_json["position"].get<Vector3>() : Vector3(0);
        camera = new PerspectiveCamera(fov, jitter, focalDistance, lenseRadius, width, height, samples, direction, position);
    } else if (type == "OrthographicCamera") {
        double scale = camera_json.contains("scale") ? camera_json["scale"].get<double>() : 1;
        bool jitter = camera_json.contains("jitter") ? camera_json["jitter"].get<bool>() : true;
        Vector3 direction = camera_json.contains("direction") ? camera_json["direction"].get<Vector3>() : Vector3(1, 0, 0);
        direction.normalize();
        Vector3 position = camera_json.contains("position") ? camera_json["position"].get<Vector3>() : Vector3(0);
        camera = new OrthographicCamera(scale, jitter, width, height, samples, direction, position);
    } else {
        throw std::runtime_error("Camera type doesn't exist");
    }
    return camera;
}