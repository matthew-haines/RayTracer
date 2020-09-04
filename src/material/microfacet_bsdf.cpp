#include "microfacet_bsdf.hpp"
#include "../helpers.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include <cmath>

MicrofacetBSDF::MicrofacetBSDF(const double refractionIndex, Fresnel* const fresnelFunction, MicrofacetDistribution* const microfacetDistribution): BxDF(false), refractionIndex(refractionIndex), fresnelFunction(fresnelFunction), microfacetDistribution(microfacetDistribution) {}

Vector3 MicrofacetBSDF::evaluate(const Vector3 negin, const Vector3 normal, const Vector3 out) const {
    Vector3 in = -negin;
    bool reflection = positiveCharacteristic(normal.dot(in)) && positiveCharacteristic(normal.dot(out));
    Vector3 h;
    double fresnel;
    if (reflection) {
        h = (sign(normal.dot(in))*(out+in)).normalized();
        fresnel = (*fresnelFunction)(in.dot(h), refractionIndex, 1);
        return microfacetDistribution->Distribution(h, normal) * microfacetDistribution->Geometry(in, out, h, normal) * fresnel / (4 * std::abs(normal.dot(in)*out.dot(normal)));
    } else {
        double jacobian;
        bool entering = normal.dot(in) > 0;
        if (entering) {
            h = (refractionIndex * out + in).normalized();
            h = -h;
            jacobian = square(refractionIndex) * std::abs(out.dot(h)) / square(h.dot(in) + refractionIndex * (out.dot(h)));
        } else {
            h = (out + refractionIndex * in).normalized();
            h = -h;
            jacobian = std::abs(out.dot(h)) / square(refractionIndex * h.dot(in) + out.dot(h));
        }
        fresnel = 1 - (*fresnelFunction)(in.dot(h), refractionIndex, 1);
        return std::abs(in.dot(h) / (in.dot(normal) * out.dot(normal))) * jacobian * microfacetDistribution->Distribution(h, normal) * microfacetDistribution->Geometry(in, out, h, normal) * fresnel;
    }
}

Vector3 MicrofacetBSDF::sample(const Vector3 in, const Vector3 normal) {
    Vector3 m = Matrix3::createFromNormal(normal) * microfacetDistribution->Sample(dist(gen), dist(gen));
    double fresnel = (*fresnelFunction)(-in.dot(m), refractionIndex, 1);
    double u = dist(gen);
    if (u < fresnel) {
        // Reflect
        return SpecularReflectBRDF::getReflection(in, m);
    } else {
        // Transmit
        return SpecularRefractBTDF::getRefraction(in, m, refractionIndex);
    }
}

double MicrofacetBSDF::pdf(const Vector3 negin, const Vector3 normal, const Vector3 out) const {
    Vector3 in = -negin;
    bool reflection = positiveCharacteristic(in.dot(normal)) && positiveCharacteristic(normal.dot(out));
    double jacobian;
    Vector3 h;
    double fresnel;
    if (reflection) {
        h = (sign(normal.dot(in))*(out+in)).normalized();
        fresnel = (*fresnelFunction)(in.dot(h), refractionIndex, 1);
        jacobian = 1 / (4 * std::abs(out.dot(h)));
    } else {
        bool entering = normal.dot(in) > 0;
        if (entering) {
            h = (refractionIndex * out + in).normalized();
            h = -h;
            jacobian = square(refractionIndex) * std::abs(out.dot(h)) / square(h.dot(in) + refractionIndex * (out.dot(h)));
        } else {
            h = (out + refractionIndex * in).normalized();
            h = -h;
            jacobian = std::abs(out.dot(h)) / square(refractionIndex * h.dot(in) + out.dot(h));
        }
        fresnel = 1 - (*fresnelFunction)(in.dot(h), refractionIndex, 1);
    }
    double hProbability = microfacetDistribution->Distribution(h, normal) * h.dot(normal);
    return hProbability * jacobian * fresnel;
}

Vector3 MicrofacetBSDF::operator()(const Vector3 negin, const Vector3 normal, Vector3& out, double& probability) {
    Vector3 in = -negin;
    Vector3 m = Matrix3::createFromNormal(normal) * microfacetDistribution->Sample(dist(gen), dist(gen));
    double fresnel = (*fresnelFunction)(in.dot(m), refractionIndex, 1);
    double u = dist(gen); 
    double jacobian;
    if (u < fresnel) {
        // Reflect
        out = SpecularReflectBRDF::getReflection(negin, m);
        jacobian = 1 / (4 * std::abs(out.dot(m)));
        double distribution = microfacetDistribution->Distribution(m, normal);
        probability = distribution * m.dot(normal) * jacobian * fresnel;
        return distribution * microfacetDistribution->Geometry(in, out, m, normal) / (4 * std::abs(in.dot(normal) * out.dot(normal))) * fresnel;
    } else {
        // Transmit
        out = SpecularRefractBTDF::getRefraction(negin, m, refractionIndex);
        bool entering = normal.dot(in) > 0;
        if (entering) {
            jacobian = square(refractionIndex) * std::abs(out.dot(m)) / square(m.dot(in) + refractionIndex * (out.dot(m)));
        } else {
            jacobian = std::abs(out.dot(m)) / square(refractionIndex * m.dot(in) + out.dot(m));
        }
        double distribution = microfacetDistribution->Distribution(m, normal);
        probability = distribution * m.dot(normal) * jacobian * (1 - fresnel);
        return std::abs(in.dot(m) / (in.dot(normal) * out.dot(normal))) * jacobian * distribution * microfacetDistribution->Geometry(in, out, m, normal) * (1 - fresnel);
    }
}