#include <iostream>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <random>

using namespace std;
using namespace std::chrono;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> random_rand(0, 1);
    std::srand(2903);

    int samples=1000000;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
        double result = random_rand(gen);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
        double result = ((double)std::rand()) / RAND_MAX;
    }
    stop = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop - start);
    cout << "CRand: " << duration.count() << endl << "random rand: " << duration2.count() << endl << samples << " samples";
}