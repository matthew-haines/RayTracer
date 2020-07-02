#include "color.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "cameras.hpp"
#include "lighting_models.hpp"
#include "point_light.hpp"
#include "naive_intersector.hpp"
#include "constants.hpp"
#include "primitive.hpp"
#include "lodepng.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

Color ambient(0.1, 0.1, 0.1);
Surface matte = {0.8, 0.1, 0.0, 1.3, Color(0.5, 0.25, 0.25)};
Surface vacuum = {0.0, 0.0, 0.0, 1.0, {0.0, 0.0, 0.0}};

void RenderRange(int start, int stop, SimpleLightingModel *lightingModel, std::vector<Ray> *rays, std::vector<unsigned char> *buffer) {
    int bufferIndex = 4 * start;
    for (int i = start; i < stop; i++) {
        Color result = lightingModel->evaluate((*rays)[i], 0);
        (*buffer)[bufferIndex] = ColorToChar(result.r);
        (*buffer)[++bufferIndex] = ColorToChar(result.g);
        (*buffer)[++bufferIndex] = ColorToChar(result.b);
        (*buffer)[++bufferIndex] = 255;
        bufferIndex++;
    }
}

int main() {
    int threads=8;
    int width=1000, height=1000;

    std::cout << "Generating Data Structures" << std::endl;

    std::vector<PointLight> lights; 
    lights.push_back({Vector3(0.0, 1.0, 4.0), Color(1.0, 1.0, 1.0)});
    
    std::vector<Primitive*> primitives;
    Sphere sphere(Vector3(6.0, 0.0, 0.0), 1.0);
    sphere.surface = &matte;
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