#ifndef GGX_BSDF_HPP
#define GGX_BSDF_HPP
#include "bxdf.hpp"

class GGXBSDF: public BxDF {
    public:
        double alpha;
        double albedo;
        double refractionIndex;
        GGXBSDF(double alpha, double albedo, double refractionIndex);
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
};

#endif