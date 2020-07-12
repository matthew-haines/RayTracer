#ifndef LAMBERTIAN_BRDF
#define LAMBERTIAN_BRDF
#include "bxdf.hpp"

class LambertianBRDF: public BxDF {
    public:
        double albedo;
        LambertianBRDF(double albedo);
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3& out, double& probability, bool importanceSample);
};

#endif
