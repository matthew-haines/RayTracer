#include "vector3.hpp"
#include "camera/perspective_camera.hpp"
#include "scene.hpp"
#include "lighting/pathtracer.hpp"
#include "lighting/pathtracermis.hpp"
#include "intersector/naive_intersector.hpp"
#include "intersector/bvh_intersector.hpp"
#include "../lib/json/json.hpp"
#include "reader/camera_reader.hpp"
#include "reader/scene_reader.hpp"
#include <cmath>
#include <fstream>
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

using json = nlohmann::json;

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
    std::ifstream f(infilename);
    json j;
    f >> j;
    Camera* camera = ParseCamera(j, width, height);
    Scene scene = ParseScene(j);
    
    BVHIntersector intersector(&scene);
    PathTracerMIS model(intersector, 4, Vector3(0.));

    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    model.Render(*camera, threads, samples);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    camera->Write(outfilename);
}