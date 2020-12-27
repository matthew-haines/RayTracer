#include <istream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fresnel.hpp"
#include <iostream>
#include <string>

TEST_CASE("FresnelCorrectnessTest", "[fresnel]") {
    double refractionIndex = 1.5;
    int n = 10;
    using namespace std;
    cout << left << setw(12) << " theta" << left << setw(12) << " cos(theta)" << left << setw(12) << " f(theta)" << std::endl;
    for (int i = 0; i < n; i++) {
        double theta = M_PI - M_PI * ((double)i / n);
        cout << right << setw(12) << to_string(theta) + "," << right << setw(12) << to_string(cos(theta)) + "," << right << setw(12) << FresnelDielectric(cos(theta), refractionIndex, 1) << endl;
   }
}