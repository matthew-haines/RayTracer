#ifndef LAMBERTIAN_BRDF
#define LAMBERTIAN_BRDF

#include "bxdf.hpp"

class LambertianBRDF: public BxDF {
    private:
        const double albedo;
    public:
        LambertianBRDF(double albedo);
        Vector3 evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif
