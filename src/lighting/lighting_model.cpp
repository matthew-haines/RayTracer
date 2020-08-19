#include "lighting_model.hpp"
#include <thread>

LightingModel::LightingModel(Intersector& intersector, int maxDepth, Vector3 ambient): intersector(intersector), maxDepth(maxDepth), ambient(ambient) {};

void LightingModel::Render(Camera& camera, int threads, int samples) {
    auto workerFunction = [this, &camera, samples]() {
        while (true) {
            Vector3* location = nullptr;
            auto rayGen = camera.Next(&location);
            if (location == nullptr) {
                break;
            }
            Vector3 accumulator(0.);
            for (int i = 0; i < samples; i++) {
                accumulator += Evaluate(rayGen(), 1);
            }
            accumulator /= samples;
            *location = accumulator;
        }
    };

    std::vector<std::thread> threadpool;
    for (int i = 0; i < threads; i++) {
        threadpool.emplace_back(workerFunction);
    }

    for (auto& thread : threadpool) {
        thread.join();
    }
}