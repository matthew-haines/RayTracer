#ifndef MICROFACET_HPP
#define MICROFACET_HPP

#include "../vector3.hpp"

class MicrofacetDistribution {
    public:
        MicrofacetDistribution() {};
        virtual double Distribution(const Vector3 m, const Vector3 n) const=0;
        virtual double Geometry(const Vector3 i, const Vector3 o, const Vector3 m, const Vector3 n) const=0;
        // Returns in spherical coordinates
        virtual Vector3 Sample(const double e1, const double e2) const=0;
};

class BeckmannDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
        const double alpha2;
    public:
        BeckmannDistribution(const double alpha);
        double Distribution(const Vector3 m, const Vector3 n) const;
        double Geometry(const Vector3 i, const Vector3 o, const Vector3 m, const Vector3 n) const;
        Vector3 Sample(const double e1, const double e2) const;
};

class PhongDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
    public:
        PhongDistribution(const double alpha);
        double Distribution(const Vector3 m, const Vector3 n) const;
        double Geometry(const Vector3 i, const Vector3 o, const Vector3 m, const Vector3 n) const;
        Vector3 Sample(const double e1, const double e2) const;
};

class GGXDistribution: public MicrofacetDistribution {
    private:
        const double alpha;
        const double alpha2;
    public:
        GGXDistribution(const double alpha);
        double Distribution(const Vector3 m, const Vector3 n) const;
        double Geometry(const Vector3 i, const Vector3 o, const Vector3 m, const Vector3 n) const;
        Vector3 Sample(const double e1, const double e2) const;
};

#endif