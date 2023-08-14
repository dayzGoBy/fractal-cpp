#include "renderer.hpp"
#include <thread>
#include <algorithm>

namespace rr {
    inline unsigned char convert(double x) {
        return (x > 255) ? 255u : (x < 0) ? 0 : static_cast<unsigned char>(x);
    }

    inline RGBA to_RGBA(double r, double g, double b, double a = 255) {
        return {convert(r), convert(g), convert(b), convert(a)};
    }

    constexpr double lambda_min = -2.55;
    constexpr double lambda_max = 0.3959;

    // TODO: parallel
    void compute_lyapunov(Cart xlim, Cart ylim, unsigned int N, Shape shape, std::vector<unsigned char> &to) {
        to = std::vector<unsigned char>(shape.first * shape.second * 4);

        const auto xstep = (xlim.second - xlim.first) / shape.first;
        const auto ystep = (ylim.second - ylim.first) / shape.second;

        const auto nthreads = 10;
        std::vector<std::thread> threads(nthreads);
        {
            unsigned for_one = shape.second / nthreads;
            for (unsigned thr = 0; thr < nthreads; thr++) {
                threads[thr] = std::thread(
                        [&](size_t number) {
                            auto y = ylim.first + number * for_one * ystep;
                            for (unsigned yc = number * for_one; yc < (number + 1) * for_one; yc++) {
                                auto x = xlim.first;
                                for (unsigned xc = 0; xc < shape.second; xc++) {
                                    auto rgba = classic(ftl::lyapunov_exponent(x, y, N));
                                    size_t index = ((shape.second - yc - 1) * shape.first + xc) * 4;

                                    to[index] = rgba.R;
                                    to[index + 1] = rgba.G;
                                    to[index + 2] = rgba.B;
                                    to[index + 3] = rgba.A;

                                    x += xstep;
                                }
                                y += ystep;
                            }
                        },
                        thr);
            }

            /*for (unsigned yc = 0; yc < shape.first; yc++) {
                auto x = xlim.first;
                for (unsigned xc = 0; xc < shape.second; xc++) {
                    auto rgba = classic(ftl::lyapunov_exponent(x, y, N));

                    size_t index = (yc * shape.first + xc) * 4;
                    to[index] = rgba.R;
                    to[index + 1] = rgba.G;
                    to[index + 2] = rgba.B;
                    to[index + 3] = rgba.A;

                    x += xstep;
                }
                y += ystep;
            }*/

            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }
    }

    RGBA classic(double val) {
        double r = 0;
        double g = 0;
        double b;
        if (val > 0) {
            b = 255 * val / lambda_max;
        } else {
            r = 255 * (1 - pow(val / lambda_min, 1 / 3.0));
            g = 255 * (1 - pow(val / lambda_min, 2 / 3.0));
            b = 0;
        }

        return to_RGBA(r, g, b);
    }

    void save(std::string name, std::vector<unsigned char> &from, rr::Shape shape) {
        unsigned error = lodepng::encode(name, from, shape.first, shape.second);

        if (error) {
            std::cerr << "LODEPNG: encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }
}
