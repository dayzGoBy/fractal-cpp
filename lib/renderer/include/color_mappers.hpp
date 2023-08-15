#ifndef COLOR_MAPPERS_HPP
#define COLOR_MAPPERS_HPP

#include "renderer_general.hpp"
#include <complex>
#include <array>

namespace rr::color_mappers {
    constexpr double MIN_LAMBDA = -2.55;
    constexpr double MAX_LAMBDA = 0.3959;
    constexpr std::array<RGBA, 5> PALETTE{
            {
                    {0, 0, 0, 255},
                    {72, 55, 255, 255},
                    {56, 255, 181, 255},
                    {139, 13, 255, 255},
                    {0, 137, 215, 255}
            }
    };
    constexpr RGBA BLACK = {0, 0, 0, 255};

    inline unsigned char convert(double x) {
        return (x > 255) ? 255u : (x < 0) ? 0 : static_cast<unsigned char>(x);
    }

    inline RGBA to_RGBA(double r, double g, double b, double a = 255) {
        return {convert(r), convert(g), convert(b), convert(a)};
    }

    rr::RGBA classic(double val);

    rr::RGBA newton(std::complex<double> val, std::vector<std::complex<double>> &&roots);

    rr::RGBA julia_bool(unsigned val);

    rr::RGBA julia_unsigned_green(unsigned val, unsigned nmax);

    rr::RGBA julia_unsigned_violet(unsigned val, unsigned nmax);

    rr::RGBA julia_unsigned_light(unsigned val, unsigned nmax);
}

#endif