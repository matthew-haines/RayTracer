#ifndef FRESNEL_SPECULAR_BSDF_HPP
#define FRESNEL_SPECULAR_BSDF_HPP
#include "bxdf.hpp"

class FresnelSpecularBSDF: public BxDF {
    public:
        double refractionIndex;
        FresnelSpecularBSDF(double refractionIndex);
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif
