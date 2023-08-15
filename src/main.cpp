#include <iostream>
#include <vector>
#include "renderer.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "the only arg is filename" << std::endl;
    }
    rr::Shape shape = {2000, 2000};
    /*std::vector<unsigned char> image =
            rr::compute_pixels(
                    {2, 4}, {2, 4}, shape,
                    [](double x, double y) {
                        return rr::color_mappers::classic(
                                ftl::lyapunov_exponent(x, y,
                                                       "ABBABAABBAABABBABAABBBABBBAA",
                                                       1e3));
                    });*/

    unsigned N = 1e4;
    std::vector<unsigned char> image =
            rr::compute_pixels(
                    {-1.35, 1.35}, {-1.35, 1.35}, shape,
                    [&N](double x, double y) {
                        return rr::color_mappers::julia_unsigned_light(
                                ftl::quadratic_julia_set({x, y}, {0.4, -0.22}, N),
                                N
                        );
                    }
            );
    rr::save(argv[1], image, shape);
}

/*std::vector<unsigned char> image =
            rr::compute_pixels(
                    {0, 4}, {0, 4}, shape,
                    [](double x, double y) {
                        return rr::color_mappers::newton(
                                ftl::newton_method(
                                        x, y,
                                        [](std::complex<double> z) {
                                            return (z - std::complex<double>(1, 1)) *
                                                   (z - std::complex<double>(3, 3))
                                                   * (z - std::complex<double>(1, 2)) *
                                                   (z - std::complex<double>(3, 1));
                                        },
                                        [](std::complex<double> z) {
                                            return std::complex<double>(4) * z * z * z +
                                                   std::complex<double>(24, 21) * z * z +
                                                   std::complex<double>(10, 82) * z +
                                                   std::complex<double>(42, 56);
                                        }
                                ),
                                {{1, 1}, {3, 3}, {1, 2}, {3, 1}}
                        );
                    }
            );*/