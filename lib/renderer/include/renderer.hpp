#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "lodepng.h"
#include <valarray>
#include <iostream>
#include <thread>
#include <algorithm>
#include "fractal.hpp"
#include "renderer_general.hpp"
#include "color_mappers.hpp"

namespace rr {
    template<typename Callable, typename... Args>
    Buffer compute_pixels(Cart xlim, Cart ylim, Shape shape, Callable&& f, Args&&... args) {
        // TODO: static_assert(); that eth is ok

        auto res = Buffer(shape.first * shape.second * 4);

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
                                    auto rgba = color_mappers::classic(f(x, y, args...));
                                    size_t index = ((shape.second - yc - 1) * shape.first + xc) * 4;
                                    res[index] = rgba.R;
                                    res[index + 1] = rgba.G;
                                    res[index + 2] = rgba.B;
                                    res[index + 3] = rgba.A;
                                    x += xstep;
                                }
                                y += ystep;
                            }
                        },
                        thr);
            }
            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }

        return res;
    }

    void save(std::string name, std::vector<unsigned char> &from, Shape shape);

    namespace color_mappers {
        RGBA classic(double val);
    }
}

#endif