#ifndef ANISTROPIC_PHONG_BRDF_HPP
#define ANISTROPIC_PHONG_BRDF_HPP

#include "bxdf.hpp"

// Ashikhmin, M., and P. Shirley 2002. An anisotropic Phong BRDF model. Journal of Graphics Tools 5 (2), 25–32.
class AnistropicPhongBRDF: public BxDF {
    private:
        const double kd;
        const double ks;
        const double nu;
        const double nv;
        double rho;
    public:
        AnistropicPhongBRDF(const double kd, const double ks, const double nu, const double nv);
        Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 sample(const Vector3 in, const Vector3 normal);
        double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const;
        Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability);
};

#endif
