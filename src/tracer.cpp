#include "vector3.hpp"
#include "ray.hpp"
#include "primitive/sphere.hpp"
#include "primitive/plane.hpp"
#include "material/material.hpp"
#include "camera/cameras.hpp"
#include "material/lambertian_brdf.hpp"
#include "scene.hpp"
#include "material/perfect_specular_brdf.hpp"
#include "lighting/pathtracer.hpp"
#include "lighting/pathtracermis.hpp"
#include "lighting/lighting_model.hpp"
#include "intersector/naive_intersector.hpp"
#include "intersector/bvh_intersector.hpp"
#include "constants.hpp"
#include "reader/reader.hpp"
#include "primitive/primitive.hpp"
#include "helpers.hpp"
#include "../lib/lodepng/lodepng.h"
#include <cmath>
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
int width = 100, height = 100;
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
    std::cout << "Using " << threads << " threads" << std::endl;

    totalPixels = width * height;    

    std::cout << "Generating Data Structures" << std::endl;
    
    Scene scene = ParseSceneFromFile(infilename);

    BVHIntersector intersector(&scene);
    PathTracerMIS model(intersector, 4, Vector3(0.));
    std::vector<Ray> rays = PerspectiveCamera(width, height, M_PI_2, Vector3(1, 0, 0));

    std::vector<unsigned char> buffer(totalPixels * 4);

    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Vector3> result = model.Render(rays, threads, samples);

    std::function<void(int)> charConv = [&buffer, &result](int index) {
        int baseIndex = index * 4;
        buffer[baseIndex] = ColorToChar(std::pow(result[index].x(), 1/2.2));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].y(), 1/2.2));
        buffer[++baseIndex] = ColorToChar(std::pow(result[index].z(), 1/2.2));
        buffer[++baseIndex] = 255;
    };

    ParallelizeLoop(threads, charConv, totalPixels);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    unsigned error = lodepng::encode(outfilename, buffer, width, height);
    if (error) {
        std::cout << "Encoding error: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}