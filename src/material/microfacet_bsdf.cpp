#include "microfacet_bsdf.hpp"
#include "../helpers.hpp"
#include "specular_reflect_brdf.hpp"
#include "specular_refract_btdf.hpp"
#include <cmath>

MicrofacetBSDF::MicrofacetBSDF(double refractionIndex, Fresnel* fresnelFunction, MicrofacetDistribution* microfacetDistribution): BxDF(false), refractionIndex(refractionIndex), fresnelFunction(fresnelFunction), microfacetDistribution(microfacetDistribution) {}

Vector3 MicrofacetBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    in = -in;
    bool reflection = PositiveCharacteristic(normal.dot(in)) && PositiveCharacteristic(normal.dot(out));
    double jacobian;
    double fresnel = (*fresnelFunction)(in.dot(normal), 1, refractionIndex);
    Vector3 h;
    if (reflection) {
        h = (sign(normal.dot(in))*(out+in)).normalized();
        jacobian = 1 / (4 * normal.dot(in) *out.dot(h));
        return microfacetDistribution->Distribution(h, normal) * microfacetDistribution->Geometry(in, out, h, normal) * jacobian * fresnel;
    } else {
        bool entering = normal.dot(in) > 0;
        if (entering) {
            h = (refractionIndex * out + in).normalized();
            h = -h;
            jacobian = square(refractionIndex) * out.dot(h) / square(h.dot(in) + refractionIndex * (out.dot(h)));
        } else {
            h = (out + refractionIndex * in).normalized();
            h = -h;
            jacobian = out.dot(h) / square(refractionIndex * h.dot(in) + out.dot(h));
        }
        return in.dot(h) / (in.dot(normal) * out.dot(normal)) * jacobian * microfacetDistribution->Distribution(h, normal) * microfacetDistribution->Geometry(in, out, h, normal) * (1 - fresnel);
    }
}

Vector3 MicrofacetBSDF::Sample(Vector3 in, Vector3 normal) {
    double fresnel = (*fresnelFunction)(-in.dot(normal), 1, refractionIndex);
    Vector3 m = Matrix3::createFromNormal(normal) * microfacetDistribution->Sample(dist(gen), dist(gen));
    double u = dist(gen);
    if (u < fresnel) {
        // Reflect
        return SpecularReflectBRDF::GetReflection(in, m);
    } else {
        // Transmit
        return SpecularRefractBTDF::GetRefraction(in, m, refractionIndex);
    }
}

double MicrofacetBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {
    in = -in;
    bool refraction = PositiveCharacteristic(normal.dot(in)) && PositiveCharacteristic(normal.dot(out));
    double jacobian;
    double fresnel = (*fresnelFunction)(in.dot(normal), 1, refractionIndex);
    Vector3 h;
    if (refraction) {
        h = (sign(normal.dot(in))*(out+in)).normalized();
        jacobian = 1 / (4 * out.dot(h));
    } else {
        bool entering = normal.dot(in) > 0;
        if (entering) {
            h = (refractionIndex * out + in).normalized();
            h = -h;
            jacobian = square(refractionIndex) * out.dot(h) / square(h.dot(in) + refractionIndex * (out.dot(h)));
        } else {
            h = (out + refractionIndex * in).normalized();
            h = -h;
            jacobian = out.dot(h) / square(refractionIndex * h.dot(in) + out.dot(h));
        }
        fresnel = 1 - fresnel;
    }
    double hProbability = microfacetDistribution->Distribution(h, normal) * h.dot(normal);
    return hProbability * jacobian * fresnel;
}

Vector3 MicrofacetBSDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {
    in = -in;
    double fresnel = (*fresnelFunction)(in.dot(normal), 1, refractionIndex);
    Vector3 m = Matrix3::createFromNormal(normal) * microfacetDistribution->Sample(dist(gen), dist(gen));
    double u = dist(gen);
    double jacobian;
    if (u < fresnel) {
        // Reflect
        out = SpecularReflectBRDF::GetReflection(-in, m);
        jacobian = 1 / (4 * out.dot(m));
        double distribution = microfacetDistribution->Distribution(m, normal);
        probability = distribution * m.dot(normal) * jacobian * fresnel;
        return distribution * microfacetDistribution->Geometry(in, out, m, normal) * jacobian * fresnel;
    } else {
        // Transmit
        out = SpecularRefractBTDF::GetRefraction(-in, m, refractionIndex);
        bool entering = normal.dot(in) > 0;
        if (entering) {
            jacobian = square(refractionIndex) * out.dot(m) / square(m.dot(in) + refractionIndex * (out.dot(m)));
        } else {
            jacobian = out.dot(m) / square(refractionIndex * m.dot(in) + out.dot(m));
        }
        double distribution = microfacetDistribution->Distribution(m, normal);
        probability = distribution * m.dot(normal) * jacobian * (1 - fresnel);
        return in.dot(m) / (in.dot(normal) * out.dot(normal)) * jacobian * distribution * microfacetDistribution->Geometry(in, out, m, normal) * (1 - fresnel);
    }
}