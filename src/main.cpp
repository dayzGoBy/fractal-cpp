#include <iostream>
#include <vector>
#include "renderer.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "the only arg is filename" << std::endl;
    }
    rr::Shape shape = {10000, 10000};
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
    std::vector<unsigned char> image =
            rr::compute_pixels(
                    {3.841, 3.855}, {3.841, 3.855}, shape,
                    [](double x, double y){
                        return rr::color_mappers::classic(ftl::lyapunov_exponent(x, y, 1e2));
                    });
    rr::save(argv[1], image, shape);
}