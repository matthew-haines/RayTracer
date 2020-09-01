#ifndef ANISTROPIC_PHONG_BRDF_HPP
#define ANISTROPIC_PHONG_BRDF_HPP
#include "bxdf.hpp"

// Ashikhmin, M., and P. Shirley 2002. An anisotropic Phong BRDF model. Journal of Graphics Tools 5 (2), 25–32.
class AnistropicPhongBRDF: public BxDF {
    private:
        double kd;
        double ks;
        double nu;
        double nv;
        double rho;
    public:
        AnistropicPhongBRDF(double kd, double ks, double nu, double nv);
        Vector3 evaluate(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 sample(Vector3 in, Vector3 normal);
        double pdf(Vector3 in, Vector3 normal, Vector3 out);
        Vector3 operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability);
};

#endif
