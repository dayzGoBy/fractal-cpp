#include "renderer.hpp"
#include <thread>
#include <algorithm>

namespace rr {
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
                                    auto rgba = color_mappers::classic(ftl::lyapunov_exponent(x, y, N));
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
            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }
    }

    void save(std::string name, std::vector<unsigned char> &from, rr::Shape shape) {
        unsigned error = lodepng::encode(name, from, shape.first, shape.second);

        if (error) {
            std::cerr << "LODEPNG: encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }
}