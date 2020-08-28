#ifndef FRESNEL_HPP
#define FRESNEL_HPP

class Fresnel {
    public:
        Fresnel() {};
        virtual double operator()(double cosI, double etaI, double etaT)=0;
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

class FixedFresnel: public Fresnel {
    private:
        double ratio;
    public:
        FixedFresnel(double ratio): ratio(ratio) {};
        double operator()(double cosI, double etaI, double etaT);
};

double FresnelDielectric(double ndoti, double etaT, double etaI);

#endif