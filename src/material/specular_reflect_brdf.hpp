#ifndef SPECULAR_REFLECT_BRDF_HPP
#define SPECULAR_REFLECT_BRDF_HPP
#include "bxdf.hpp"

class SpecularReflectBRDF: public BxDF {
    public:
        SpecularReflectBRDF();
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        static Vector3 GetReflection(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif