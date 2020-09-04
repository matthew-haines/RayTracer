#ifndef BXDF_HPP
#define BXDF_HPP

#include "../vector3.hpp"
#include <random>

class BxDF {
    protected:
        std::mt19937 gen;
        std::uniform_real_distribution<double> dist;
    public:
        // Single method that gets view vector and normal, returns spectrum and can importance sample if required
        const bool specular;
        BxDF(const bool specular);
        virtual Vector3 evaluate(const Vector3 in, const Vector3 normal, const Vector3 out) const=0;
        virtual Vector3 sample(const Vector3 in, const Vector3 normal)=0;
        virtual double pdf(const Vector3 in, const Vector3 normal, const Vector3 out) const=0;
        virtual Vector3 operator()(const Vector3 in, const Vector3 normal, Vector3& out, double& probability)=0;
};

#endif