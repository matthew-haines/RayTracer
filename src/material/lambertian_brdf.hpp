#ifndef LAMBERTIAN_BRDF
#define LAMBERTIAN_BRDF

#include "bxdf.hpp"

class LambertianBRDF: public BxDF {
    private:
        const double albedo;
    public:
        LambertianBRDF(const double albedo);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif
