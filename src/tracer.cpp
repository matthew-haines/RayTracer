#include "vector3.hpp"
#include "perspective_camera.hpp"
#include "scene.hpp"
#include "pathtracer.hpp"
#include "pathtracermis.hpp"
#include "naive_intersector.hpp"
#include "bvh_intersector.hpp"
#include "json.hpp"
#include "camera_reader.hpp"
#include "scene_reader.hpp"
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
int samples = 128;
int threads = 0;
int width = 100, height = 100;
int totalPixels;
int completedPixels = 0;
int depth = 4;
std::string infilename;
std::string outfilename("out.png");

static struct option long_options[] = {
    {"help", no_argument, 0, 'H'},
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
            case 'H':
                std::cout << "Usage: tracer [OPTION]... [IMAGE]" << std::endl << std::endl;
                std::cout << "Arguments:" << std::endl;
                std::cout << "  -i, --input       path to json scene file" << std::endl;
                std::cout << "  -t, --threads     number of threads used by tracer" << std::endl;
                std::cout << "  -w, --width       width of output image" << std::endl;
                std::cout << "  -h, --height      height of output image" << std::endl;
                std::cout << "  -s, --size        can be used instead of width/height to specify square size of output image" << std::endl;
                std::cout << "  -s, --size        can be used instead of width/height to specify square size of output image" << std::endl;
                std::cout << "  -c, --count       number of samples taken per pixel" << std::endl;
                std::cout << "  --help            help" << std::endl;
                return 0;

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
    if ((samples & (samples - 1)) != 0) {
        std::cout << "WARNING: Sample count is not a power of 2, Sobol sampling will be suboptimal." << std::endl;
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
    Camera* camera = parseCamera(j, width, height, samples);
    Scene scene = parseScene(j);
    
    BVHIntersector intersector(&scene, threads);
    PathTracerMIS model(intersector, depth, Vector3(0.));

    std::cout << "Rendering" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    model.render(*camera, threads, samples);

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "Writing" << std::endl;

    camera->write(outfilename);
}