#ifndef COLOR_MAPPERS_HPP
#define COLOR_MAPPERS_HPP

#include "renderer_general.hpp"

namespace rr::color_mappers{
    constexpr double lambda_min = -2.55;
    constexpr double lambda_max = 0.3959;

    inline unsigned char convert(double x) {
        return (x > 255) ? 255u : (x < 0) ? 0 : static_cast<unsigned char>(x);
    }

    inline RGBA to_RGBA(double r, double g, double b, double a = 255) {
        return {convert(r), convert(g), convert(b), convert(a)};
    }

    rr::RGBA classic(double val);

}

#endif