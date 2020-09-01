#include "anistropic_phong_brdf.hpp"
#include "../helpers.hpp"
#include "specular_reflect_brdf.hpp"
#include <cmath>

AnistropicPhongBRDF::AnistropicPhongBRDF(double kd, double ks, double nu, double nv): BxDF(false), kd(kd), ks(ks), nu(nu), nv(nv) {
    rho = std::sqrt((nu + 1) * (nv + 1)) / (8 * M_PI);
}

Vector3 AnistropicPhongBRDF::evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    Vector3 h = (out - in).normalized();
    Vector3 u = normal.cross(normal.z < 0.99 ? Vector3(0, 0, 1) : Vector3(1, 0, 0)).normalized();
    Vector3 v = normal.cross(u).normalized();
    Vector3 k1 = SpecularReflectBRDF::getReflection(in, normal);
    Vector3 k2 = -in;
    double ndoti = -normal.dot(in);
    double fresnel = ks + (1 - ks) * square(square(1 - ndoti)) * (1 - ndoti);
    double ndoth = normal.dot(h);
    double specular = rho * std::pow(ndoth, (nu * square(h.dot(u)) + nv * square(h.dot(v)))/(1-square(ndoth))) / (ndoti * std::max(normal.dot(k2), normal.dot(k1))) * fresnel;

    double dt1 = 1 - 0.5 * normal.dot(k1);
    double dt2 = 1 - 0.5 * normal.dot(k2);
    double diffuse = 28 * kd / (23 * M_PI) * (1 - ks) * (1 - square(square(dt1)) * dt1) * (1 - square(square(dt1)) * dt1);
    return specular + diffuse;
}

Vector3 AnistropicPhongBRDF::sample(Vector3 in, Vector3 normal) {

}

double AnistropicPhongBRDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {

}

Vector3 AnistropicPhongBRDF::operator()(Vector3 in, Vector3 normal, Vector3& out, double& probability) {

}