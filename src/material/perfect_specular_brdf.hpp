#ifndef PERFECT_SPECULAR_BRDF_HPP
#define PERFECT_SPECULAR_BRDF_HPP
#include "bxdf.hpp"

class PerfectSpecularBRDF: public BxDF {
    public:
        PerfectSpecularBRDF();
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
};

#endif