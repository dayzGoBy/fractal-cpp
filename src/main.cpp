#include <iostream>
#include <vector>
#include "renderer.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "the only arg is filename" << std::endl;
    }
    rr::Shape shape = {800, 800};
    /*std::vector<unsigned char> image =
            rr::compute_pixels(
                    {2, 4}, {2, 4}, shape,
                    [](double x, double y) {
                        return rr::color_mappers::classic(
                                ftl::lyapunov_exponent(x, y,
                                                       "ABBABAABBAABABBABAABBBABBBAA",
                                                       1e3));
                    });*/

    unsigned N = 1e3;
    /*std::vector<unsigned char> image =
            rr::compute_pixels(
                    {-1.35, 1.35}, {-1.35, 1.35}, shape,
                    [&N](double x, double y) {
                        return rr::color_mappers::julia_unsigned_two(
                                ftl::quadratic_julia_set({x, y}, {-0.13, 0.89}, N),
                                N
                        );
                    }
            );
    rr::save_png(argv[1], image, shape);*/

    unsigned frames = 50;
    rr::save_gif(argv[1],
                 [&](unsigned frame) {
                     auto x = std::pow((double) frame / frames, 2);
                     rr::Cart lim = {-0.75 + 0.7499 * x, 0.75 - 0.7499 * x};
                     return rr::compute_pixels(
                             lim, lim, shape,
                             [&N, &frame](double x, double y) {
                                 return rr::color_mappers::julia_unsigned_light(
                                         ftl::quadratic_julia_set({x, y}, {- 0.74543, 0.11301}, frame + N),
                                         N + frame
                                 );
                             }
                     );
                 }, shape, frames, 10);
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