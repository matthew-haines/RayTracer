#ifndef PHONG_BRDF_HPP
#define PHONG_BRDF_HPP
#include "bxdf.hpp"

class PhongBRDF: public BxDF {
    private:
        double kd;
        double ks;
        double n;
    public:
        PhongBRDF(double kd, double ks, double n);
        Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 Sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif