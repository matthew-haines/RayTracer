#include "lambertian_brdf.hpp"
#include "../helpers.hpp"

LambertianBRDF::LambertianBRDF(): BxDF() {}
Vector3 LambertianBRDF::evaluate(Vector3 in, Vector3 normal, Vector3& out, double& weight, bool importanceSample) {

}