#include "ggx_bsdf.hpp"

GGXBSDF::GGXBSDF(double alpha, double albedo, double refractionIndex): BxDF(false), alpha(alpha), albedo(albedo), refractionIndex(refractionIndex) {}

Vector3 GGXBSDF::Evaluate(Vector3 in, Vector3 normal, Vector3 out) {
    
}

Vector3 GGXBSDF::Sample(Vector3 in, Vector3 normal) {

}

double GGXBSDF::pdf(Vector3 in, Vector3 normal, Vector3 out) {

}