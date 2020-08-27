#include "camera_reader.hpp"
#include "../camera/perspective_camera.hpp"
#include <stdexcept>

Camera* ParseCamera(json j, std::size_t width, std::size_t height) {
    json camera_json = j.at("camera");
    std::string type = camera_json.at("type").get<std::string>();
    Camera* camera;
    if (type == "PerspectiveCamera") {
        double fov = camera_json.contains("fov") ? camera_json["fov"].get<double>() : M_PI_2;
        double jitter = camera_json.contains("jitter") ? camera_json["jitter"].get<bool>() : true;
        Vector3 direction = camera_json.contains("direction") ? camera_json["direction"].get<Vector3>() : Vector3(1, 0, 0);
        direction.normalize();
        Vector3 position = camera_json.contains("position") ? camera_json["position"].get<Vector3>() : Vector3(0);
        camera = new PerspectiveCamera(fov, jitter, width, height, direction, position);
    } else {
        throw std::runtime_error("Camera type doesn't exist");
    }
    return camera;
}