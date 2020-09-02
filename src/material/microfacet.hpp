#ifndef MICROFACET_HPP
#define MICROFACET_HPP

#include "../vector3.hpp"

class MicrofacetDistribution {
    public:
        MicrofacetDistribution() {};
        virtual double Distribution(Vector3 m, Vector3 n)=0;
        virtual double Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n)=0;
        // Returns in spherical coordinates
        virtual Vector3 Sample(double e1, double e2)=0;
};

class BeckmannDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
        const double alpha2;
    public:
        BeckmannDistribution(double alpha);
        double Distribution(Vector3 m, Vector3 n);
        double Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

class PhongDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
    public:
        PhongDistribution(double alpha);
        double Distribution(Vector3 m, Vector3 n);
        double Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

class GGXDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
        const double alpha2;
    public:
        GGXDistribution(double alpha);
        double Distribution(Vector3 m, Vector3 n);
        double Geometry(Vector3 i, Vector3 o, Vector3 m, Vector3 n);
        Vector3 Sample(double e1, double e2);
};

#endif