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
        bool specular;
        BxDF(bool specular);
        virtual Vector3 Evaluate(Vector3 in, Vector3 normal, Vector3 out)=0;
        virtual Vector3 Sample(Vector3 in, Vector3 normal)=0;
        virtual double pdf(Vector3 in, Vector3 normal, Vector3 out)=0;
};

#endif