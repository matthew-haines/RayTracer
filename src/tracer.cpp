#include "vector3.hpp"
#include "ray.hpp"
#include "primitive/sphere.hpp"
#include "primitive/plane.hpp"
#include "material/material.hpp"
#include "camera/cameras.hpp"
#include "lighting/simple_lighting_model.hpp"
#include "lighting/disney_brdf_lighting_model.hpp"
#include "lighting/point_light.hpp"
#include "intersector/naive_intersector.hpp"
#include "constants.hpp"
#include "primitive/primitive.hpp"
#include "helpers.hpp"
#include "../lib/lodepng/lodepng.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>

Vector3 ambient(0.0);
int samples = 8000;
int completedPixels = 0;
int totalPixels;

void RenderRange(int start, int stop, LightingModel *lightingModel, std::vector<Ray> *rays, std::vector<unsigned char> *buffer) {
    int bufferIndex = 4 * start;
    for (int i = start; i < stop; i++) {
        Vector3 result = (0.0);
        for (int j = 0; j < samples; j++) {
            result += lightingModel->Evaluate((*rays)[i], 0);
        }
        result /= samples;
        // gamma correct all colors that were in linspace throughout processing
        (*buffer)[bufferIndex] = ColorToChar(pow(result.x, 1/2.2)); // r
        (*buffer)[++bufferIndex] = ColorToChar(pow(result.y, 1/2.2)); // g
        (*buffer)[++bufferIndex] = ColorToChar(pow(result.z, 1/2.2)); // b
        (*buffer)[++bufferIndex] = 255;
        bufferIndex++;
        completedPixels++;
        if (completedPixels % (totalPixels / 100) == 0) {
            std::cout << "\r" << 100 * completedPixels / totalPixels << "\%" << std::flush;
        }
    }
}

int main() {
    // These are required by literally everything
    int threads=8;
    int width=500, height=500;
    totalPixels = width * height;

    std::cout << "Generating Data Structures" << std::endl;
    
    std::vector<Primitive*> primitives;

    Material *light = new Material();
    light->emission = 8.0;
    light->color = Vector3(1.0);
    light->specular = 1.0;
    light->clearcoat = 1.0;
    Material *metal = new Material();
    metal->metallic = 0.8;
    metal->sheen = 0.5;
    metal->color = Vector3(0.8, 0.8, 0.8);
    Material *reflect = new Material();
    reflect->metallic = 1.0;
    reflect->color = Vector3(1.0, 1.0, 1.0);
    reflect->roughness = 0.0;
    Material *red = new Material();
    red->color = Vector3(1.0, 0.0, 0.0);
    Material *green = new Material();
    green->color = Vector3(0.0, 1.0, 0.0);
    Material *white = new Material();
    white->color = Vector3(1.0);
    Material *vacuum = new Material();

    Sphere sphere(Vector3(4.9, 0.0, 2.5), 1.0, light);
    Sphere sphere2(Vector3(4.0, 1.5, -1.5), 0.75, metal);
    Sphere sphere3(Vector3(4.0, -1.5, -1.5), 0.75, reflect);
    Plane front(Vector3(1.0, 0.0, 0.0), 2.0, white);
    Plane back(Vector3(-1.0, 0.0, 0.0), 6.0, white);
    Plane bottom(Vector3(0.0, 0.0, 1.0), 4.0, white);
    Plane top(Vector3(0.0, 0.0, -1.0), 4.0, white);
    Plane left(Vector3(0.0, -1.0, 0.0), 4.0, red);
    Plane right(Vector3(0.0, 1.0, 0.0), 4.0, green);
    primitives.push_back(&sphere);
    primitives.push_back(&sphere2);
    primitives.push_back(&sphere3);
    primitives.push_back(&front);
    primitives.push_back(&back);
    primitives.push_back(&bottom);
    primitives.push_back(&top);
    primitives.push_back(&left);
    primitives.push_back(&right);

    NaiveIntersector intersector(primitives);
    DisneyBRDFLightingModel lightingModel(ambient, &intersector, 4);
    std::vector<Ray> rays = PerspectiveCamera(width, height, M_PI_2, Vector3(1, 0, 0));

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

    std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    unsigned error = lodepng::encode("out.png", buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}