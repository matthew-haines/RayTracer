#ifndef SPECULAR_REFRACT_BTDF_HPP
#define SPECULAR_REFRACT_BTDF_HPP

#include "bxdf.hpp"

class SpecularRefractBTDF: public BxDF {
    public:
        double refractionIndex;
        SpecularRefractBTDF(double refractionIndex);
        Vector3 evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 sample(Vector3 in, Vector3 normal);
        static Vector3 getRefraction(Vector3 in, Vector3 normal, double refractionIndex);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif