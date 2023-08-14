#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <fractal.hpp>

TEST_CASE("Lyapunov exponent") {
    //REQUIRE_THAT(ftl::lyapunov_exponent(2, 3, 1e4), Catch::Matchers::WithinAbs(-0.471902, 1e-4));
    //REQUIRE_THAT(ftl::lyapunov_exponent(1, 1, 1e4), Catch::Matchers::WithinAbs(-0.00230914, 1e-6));
}