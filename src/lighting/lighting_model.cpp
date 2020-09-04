#include "lighting_model.hpp"
#include <chrono>
#include <iostream>
#include <thread>

LightingModel::LightingModel(Intersector& intersector, const int maxDepth, const Vector3 ambient): intersector(intersector), maxDepth(maxDepth), ambient(ambient) {};

void LightingModel::render(Camera& camera, const int threads, const int samples) {
    int finished = 0;
    int total = camera.width * camera.height;
    auto last = std::chrono::high_resolution_clock::now();

    auto workerFunction = [this, &camera, samples, &last, &finished, &total]() {
        while (true) {
            Vector3* location = nullptr;
            auto rayGen = camera.next(&location);
            if (location == nullptr) {
                break;
            }
            Vector3 accumulator(0.);
            Intersection nullIntersection;
            nullIntersection.primitive = nullptr;
            for (int i = 0; i < samples; i++) {
                accumulator += evaluate(rayGen(), 1, nullIntersection);
            }
            accumulator /= samples;
            *location = accumulator;
            finished++;
            if (finished % (total / 100) == 0) {
                auto now = std::chrono::high_resolution_clock::now();
                double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
                last = now;
                double remaining = 100. - (double)finished / (double)total * 100.;
                std::cout << "\r" << 100 * finished / total << "\% (" << (int)(remaining * milliseconds) / 1000 << " s)     " << std::flush;

            }
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