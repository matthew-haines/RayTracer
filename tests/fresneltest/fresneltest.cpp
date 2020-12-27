#include "fresnel.hpp"
#include <cmath>
#include <iostream>

double refractionIndex = 1.5;
int n = 100;

int main() {
    for (int i = 0; i < n; i++) {
        double cosI = -M_PI + M_PI * ((double)i / n);
        std::cout << cosI << "," << FresnelDielectric(cosI, refractionIndex, 1) << std::endl;
    }
    return 0;
}

