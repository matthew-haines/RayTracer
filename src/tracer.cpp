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
#include "reader/reader.hpp"
#include "primitive/primitive.hpp"
#include "helpers.hpp"
#include "../lib/lodepng/lodepng.h"
#include <math.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <getopt.h>

Vector3 ambient(0.0);
int samples = 100;
int threads = 0;
int width = 500, height = 500;
int totalPixels;
int completedPixels = 0;
std::string infilename;
std::string outfilename("out.png");

static struct option long_options[] = {
    {"input", required_argument, 0, 'i'},
    {"threads", required_argument, 0, 't'},
    {"width", required_argument, 0, 'w'},
    {"height", required_argument, 0, 'h'},
    {"size", required_argument, 0, 's'},
    {"count", required_argument, 0, 'c'}
};

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

int main(int argc, char *argv[]) {
    while (true) {
        int index;
        int c = getopt_long(argc, argv, "i:t:w:h:s:c:", long_options, &index);
        if (c == -1) break;
        switch (c) {
            case 'i':
                infilename = optarg;
                break;

            case 't':
                threads = atoi(optarg);
                break;
            
            case 'w':
                width = atoi(optarg);
                break;
            
            case 'h':
                height = atoi(optarg);
                break;

            case 's': 
                width = atoi(optarg);
                height = width;
                break;
            
            case 'c':
                samples = atoi(optarg);
                break;
        }
    }

    if (infilename.empty()) {
        std::cout << "No input scene file" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        outfilename = argv[optind];
    }

    if (threads == 0) {
        threads = std::thread::hardware_concurrency();
    }

    totalPixels = width * height;    

    std::cout << "Generating Data Structures" << std::endl;
    
    Scene scene = ParseSceneFromFile(infilename);

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
    for (std::size_t i = 0; i < threadpool.size(); i++) {
        threadpool[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    unsigned error = lodepng::encode(outfilename, buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}