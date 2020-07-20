#include "vector3.hpp"
#include "ray.hpp"
#include "primitive/sphere.hpp"
#include "primitive/plane.hpp"
#include "material/material.hpp"
#include "camera/cameras.hpp"
#include "lighting/uniform_sampling_model.hpp"
#include "lighting/importance_sampling_model.hpp"
#include "material/lambertian_brdf.hpp"
#include "scene.hpp"
#include "material/perfect_specular_brdf.hpp"
#include "lighting/lighting_model.hpp"
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
int samples = 10000;
int completedPixels = 0;
int totalPixels;

void RenderRange(int start, int stop, LightingModel *lightingModel, std::vector<Ray> *rays, std::vector<unsigned char> *buffer) {
    int bufferIndex = 4 * start;
    for (int i = start; i < stop; i++) {
        Vector3 result = (0.0);
        for (int j = 0; j < samples; j++) {
            result += lightingModel->Evaluate((*rays)[i], 1);
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

    LambertianBRDF lambertian = LambertianBRDF(0.50);
    PerfectSpecularBRDF specular = PerfectSpecularBRDF();

    Material *light = new Material();
    light->emission = 8.0;
    light->color = Vector3(1.0);
    light->bxdf = &lambertian;
    Material *diffuse = new Material();
    diffuse->color = Vector3(0.8, 0.8, 0.8);
    diffuse->bxdf = &lambertian;
    Material *reflect = new Material();
    reflect->color = Vector3(1.0, 1.0, 1.0);
    reflect->bxdf = &specular;
    Material *red = new Material();
    red->color = Vector3(1.0, 0.0, 0.0);
    red->bxdf = &lambertian;
    Material *green = new Material();
    green->color = Vector3(0.0, 1.0, 0.0);
    green->bxdf = &lambertian;
    Material *white = new Material();
    white->color = Vector3(1.0);
    white->bxdf = &lambertian;

    Sphere sphere(Vector3(4.9, 0.0, 2.5), 1.0, light);
    Sphere sphere2(Vector3(4.0, 1.5, -1.5), 0.75, diffuse);
    Sphere sphere3(Vector3(4.0, -1.5, -1.5), 0.75, reflect);
    Plane front(Vector3(1.0, 0.0, 0.0), 2.0, white);
    Plane back(Vector3(-1.0, 0.0, 0.0), 6.0, white);
    Plane bottom(Vector3(0.0, 0.0, 1.0), 4.0, reflect);
    Plane top(Vector3(0.0, 0.0, -1.0), 4.0, white);
    Plane left(Vector3(0.0, -1.0, 0.0), 4.0, red);
    Plane right(Vector3(0.0, 1.0, 0.0), 4.0, green);

    Scene scene;
    scene.Insert(&sphere);
    scene.Insert(&sphere2);
    scene.Insert(&sphere3);
    scene.Insert(&front);
    scene.Insert(&back);
    scene.Insert(&bottom);
    scene.Insert(&top);
    scene.Insert(&left);
    scene.Insert(&right);

    NaiveIntersector intersector(&scene);
    ImportanceSamplingModel model(ambient, &intersector, 6);
    std::vector<Ray> rays = PerspectiveCamera(width, height, M_PI_2, Vector3(1, 0, 0));

    std::vector<unsigned char> buffer(width * height * 4);

    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    int block = width * height / threads;
    std::vector<std::thread> threadpool;
    for (int i = 0; i < threads; i++) {
        threadpool.emplace_back(RenderRange, i * block, i == (threads-1) ? width * height : (i + 1) * block, &model, &rays, &buffer);
    }
    for (unsigned int i = 0; i < threadpool.size(); i++) {
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