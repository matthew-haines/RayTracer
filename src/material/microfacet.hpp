#ifndef MICROFACET_HPP
#define MICROFACET_HPP
#include "../vector3.hpp"

class MicrofacetDistribution {
    public:
        MicrofacetDistribution() {};
        virtual double Evaluate(Vector3 m, Vector3 n)=0;
        // Returns in spherical coordinates
        virtual Vector3 Sample(double e1, double e2)=0;
};

class BeckmannDistribution: public MicrofacetDistribution {
    private:
        double alpha;
        double alpha2;
    public:
        BeckmannDistribution(double alpha);
        double Evaluate(Vector3 m, Vector3 n);
        double G1(Vector3 v, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

class PhongDistribution: public MicrofacetDistribution {
    private:
        double alpha;
        double alpha2;
    public:
        PhongDistribution(double alpha);
        double Evaluate(Vector3 m, Vector3 n);
        double G1(Vector3 v, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

class GGXDistribution: public MicrofacetDistribution {
    private:
        double alpha;
        double alpha2;
    public:
        GGXDistribution(double alpha);
        double Evaluate(Vector3 m, Vector3 n);
        double G1(Vector3 v, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

#endif