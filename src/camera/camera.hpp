#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "../ray.hpp"
#include "../vector3.hpp"
#include <functional>
#include <mutex>
#include <string>
#include <vector>
#include <queue>
#include <utility>

class Camera {
    private:
        std::mutex mutex;
        std::queue<std::pair<std::function<Ray()>, Vector3*>> queue;
    protected:
        std::vector<Vector3> result;
        Matrix3 rotation;
        void buildQueue();
    public:
        std::size_t width;
        std::size_t height;
        Vector3 direction;
        Vector3 position;
        Camera(std::size_t width, std::size_t height, Vector3 direction, Vector3 position);
        void write(std::string path, double gamma = 2.2, std::size_t threads = 1);
        std::function<Ray()> next(Vector3** location);
        virtual std::function<Ray()> getPixelFunction(int row, int column)=0;
};

#endif