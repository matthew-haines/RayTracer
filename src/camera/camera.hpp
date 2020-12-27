#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include <functional>
#include <mutex>
#include <string>
#include <vector>
#include <queue>
#include <utility>

// Camera base class, provides a work queue for the render and image writing.
class Camera {
    private:
        std::mutex mutex;
        std::queue<std::pair<std::function<std::function<Ray()>()>, Vector3*> > queue;
    protected:
        std::vector<Vector3> result;
        Matrix3 rotation;
        const Vector3 direction;
        const Vector3 position;
        const int samples;
        // Returns a function that spawns rays for the given pixel.
        virtual std::function<Ray()> getPixelFunction(const int row, const int column)=0;
        // Called by derived types in order to construct the work queue based off getPixelFunction.
        void buildQueue();
    public:
        const std::size_t width;
        const std::size_t height;
        Camera(const std::size_t width, const std::size_t height, const int samples, const Vector3 direction, const Vector3 position);
        // Writes the Camera's accumulated state to the provided path, post-processing as required.
        void write(const std::string path, const double gamma = 2.2, const std::size_t threads = 1) const;
        std::function<Ray()> next(Vector3** location);
};

#endif