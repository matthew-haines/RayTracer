#include "specular_reflect_brdf.hpp"
#include <istream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fresnel.hpp"
#include "specular_reflect_brdf.cpp"
#include <iostream>
#include <string>

// TODO: Fix this: https://github.com/catchorg/Catch2/blob/devel/docs/slow-compiles.md#top

TEST_CASE("FresnelCorrectnessTest", "[.fresnel]") {
    double refractionIndex = 1.5;
    int n = 10;
    using namespace std;
    cout << left << setw(12) << " theta" << left << setw(12) << " cos(theta)" << left << setw(12) << " f(theta)" << std::endl;
    for (int i = 0; i < n; i++) {
        double theta = M_PI - M_PI * ((double)i / n);
        cout << right << setw(12) << to_string(theta) + "," << right << setw(12) << to_string(cos(theta)) + "," << right << setw(12) << FresnelDielectric(cos(theta), refractionIndex, 1) << endl;
   }
}

TEST_CASE("SpecularReflectionTest", "[reflect]") {
    Vector3 in = Vector3(1, 0, -1).normalized();
    Vector3 normal(0, 0, 1);
    Vector3 out = SpecularReflectBRDF::getReflection(in, normal);
    REQUIRE(std::acos(out.dot(-in)) == Approx(2. * std::acos(normal.dot(-in))));
    REQUIRE((-in + out).normalized().z == Approx(normal.z));
}