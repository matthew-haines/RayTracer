#ifndef GGX_BSDF_HPP
#define GGX_BSDF_HPP
#include "bxdf.hpp"

class GGXBSDF: public BxDF {
    public:
        double alpha;
        double alpha2;
        double albedo;
        double transmittanceProbability;
        double refractionIndex;
        GGXBSDF(double alpha, double albedo, double refractionIndex=1, double transmittanceProbability=-1);
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif