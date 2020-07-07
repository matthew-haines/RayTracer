#include "vector3.hpp"
#include "ray.hpp"
#include "primitive/sphere.hpp"
#include "material.hpp"
#include "camera/cameras.hpp"
#include "lighting/simple_lighting_model.hpp"
#include "lighting/point_light.hpp"
#include "intersector/naive_intersector.hpp"
#include "constants.hpp"
#include "primitive/primitive.hpp"
#include "../lib/lodepng/lodepng.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

Vector3 ambient(0.1, 0.1, 0.1);
Material matte;
Material vacuum;

void RenderRange(int start, int stop, SimpleLightingModel *lightingModel, std::vector<Ray> *rays, std::vector<unsigned char> *buffer) {
    int bufferIndex = 4 * start;
    for (int i = start; i < stop; i++) {
        Vector3 result = lightingModel->Evaluate((*rays)[i], 0);
        // gamma correct all colors that were in linspace throughout processing
        (*buffer)[bufferIndex] = ColorToChar(pow(result.x, 2.2)); // r
        (*buffer)[++bufferIndex] = ColorToChar(pow(result.y, 2.2)); // g
        (*buffer)[++bufferIndex] = ColorToChar(pow(result.z, 2.2)); // b
        (*buffer)[++bufferIndex] = 255;
        bufferIndex++;
    }
}

int main() {
    int threads=8;
    int width=1000, height=1000;

    std::cout << "Generating Data Structures" << std::endl;

    std::vector<PointLight> lights; 
    lights.push_back({Vector3(0.0, 1.0, 4.0), Vector3(1.0, 1.0, 1.0)});
    
    std::vector<Primitive*> primitives;
    Sphere sphere(Vector3(6.0, 0.0, 0.0), 1.0);
    sphere.material = &matte;
    primitives.push_back(&sphere);

    NaiveIntersector intersector(primitives);
    SimpleLightingModel lightingModel(ambient, &vacuum, &intersector, lights, 4);
    std::vector<Ray> rays = PerspectiveCamera(width, height, M_PI / 3, Vector3(1, 0, 0));

    std::vector<unsigned char> buffer(width * height * 4);

    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    int block = width * height / threads;
    std::vector<std::thread> threadpool;
    for (int i = 0; i < threads; i++) {
        threadpool.emplace_back(RenderRange, i * block, i == (threads-1) ? width * height : (i + 1) * block, &lightingModel, &rays, &buffer);
    }
    for (int i = 0; i < threadpool.size(); i++) {
        threadpool[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    unsigned error = lodepng::encode("out.png", buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}