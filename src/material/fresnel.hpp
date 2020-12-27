#ifndef FRESNEL_HPP
#define FRESNEL_HPP

// Base class for the different Fresnel implementations.
class Fresnel {
    public:
        Fresnel() {};
        virtual double operator()(double cosI, double etaI, double etaT) const=0;
};

class DielectricFresnel: public Fresnel {
    public:
        DielectricFresnel() {};
        double operator()(double cosI, double etaI, double etaT) const;
};

class ReflectanceFresnel: public Fresnel {
    public:
        ReflectanceFresnel() {};
        double operator()(double cosI, double etaI, double etaT) const;
};

class TransmittanceFresnel: public Fresnel {
    public:
        TransmittanceFresnel() {};
        double operator()(double cosI, double etaI, double etaT) const;
};

class FixedFresnel: public Fresnel {
    private:
        const double ratio;
    public:
        FixedFresnel(const double ratio): ratio(ratio) {};
        double operator()(double cosI, double etaI, double etaT) const;
};

double FresnelDielectric(double ndoti, double etaT, double etaI);

#endif