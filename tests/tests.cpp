#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

TEST_CASE("TEST", "test") {
    REQUIRE(1 == 1);
    std::cout << "test2" << std::endl;
}