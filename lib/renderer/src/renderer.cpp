#include "renderer.hpp"

namespace rr {
    void save_png(std::string name, std::vector<unsigned char> &from, Shape shape) {
        unsigned error = lodepng::encode(name, from, shape.first, shape.second);

        if (error) {
            std::cerr << "LODEPNG: encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }

    Buffer compute_pixels(Cart xlim, Cart ylim, Shape shape, std::function<rr::RGBA(double, double)> &&f,
                          unsigned nthreads) {
        // TODO: static_assert(); that eth is ok

        auto res = Buffer(shape.first * shape.second * 4);

        const auto xstep = (xlim.second - xlim.first) / shape.first;
        const auto ystep = (ylim.second - ylim.first) / shape.second;

        std::vector<std::thread> threads(nthreads);
        {
            for (unsigned thr = 0; thr < nthreads; thr++) {
                threads[thr] = std::thread(
                        [&](unsigned number) {
                            auto y = ylim.first + number * ystep;
                            for (unsigned yc = number; yc < shape.second - nthreads + number + 1; yc += nthreads) {
                                auto x = xlim.first;
                                for (unsigned xc = 0; xc < shape.first; xc++) {
                                    auto rgba = f(x, y);
                                    size_t index = ((shape.second - yc - 1) * shape.first + xc) * 4;
                                    res[index] = rgba.R;
                                    res[index + 1] = rgba.G;
                                    res[index + 2] = rgba.B;
                                    res[index + 3] = rgba.A;
                                    x += xstep;
                                }
                                y += ystep * nthreads;
                            }
                        },
                        thr);
            }
            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }

        return res;
    }

    void save_gif(std::string name, std::function<std::vector<unsigned char>(unsigned int)>&& animate, Shape shape,
                  unsigned frames, unsigned int delay) {
        GifWriter writer;

        GifBegin(&writer, name.c_str(), shape.first, shape.second, delay);

        for (unsigned frame = 0; frame < frames; frame++) {
            GifWriteFrame(&writer, animate(frame).data(), shape.first, shape.second, delay);
        }

        GifEnd(&writer);
    }
}