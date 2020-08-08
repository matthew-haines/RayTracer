#include "bxdf.hpp"

BxDF::BxDF(bool specular): specular(specular) {
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0., 1.);
}