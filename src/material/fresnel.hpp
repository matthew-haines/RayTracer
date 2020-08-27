#ifndef FRESNEL_HPP
#define FRESNEL_HPP

class Fresnel {
    public:
        Fresnel() {};
        virtual double operator()(double cosI, double etaI, double etaT);
};

class DielectricFresnel: public Fresnel {
    public:
        DielectricFresnel() {};
        double operator()(double cosI, double etaI, double etaT);
};

class ReflectanceFresnel: public Fresnel {
    public:
        ReflectanceFresnel() {};
        double operator()(double cosI, double etaI, double etaT);
};

class TransmittanceFresnel: public Fresnel {
    public:
        TransmittanceFresnel() {};
        double operator()(double cosI, double etaI, double etaT);
};

double FresnelDielectric(double ndoti, double etaT, double etaI);

#endif