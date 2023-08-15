#include <valarray>
#include "color_mappers.hpp"
#include "renderer_general.hpp"

namespace rr::color_mappers {
    rr::RGBA classic(double val) {

        double r = 0;
        double g = 0;
        double b;
        if (val > 0) {
            r = 45 * val / MAX_LAMBDA;
            b = 95 * val / MAX_LAMBDA;
        } else {
            r = 255 * (1 - std::pow(val / MIN_LAMBDA, 2 / 3.0));
            g = 255 * (1 - std::pow(val / MIN_LAMBDA, 1.15 / 3.0));
            b = 255 * (1 - std::pow(val / MIN_LAMBDA, 0.45 / 3.0));
        }

        return to_RGBA(r, g, b);
    }

    rr::RGBA newton(std::complex<double> val, std::vector<std::complex<double>>&& roots) {
        size_t imin = 0;
        double dmin = std::numeric_limits<double>::max();
        for (size_t i = 0; i < roots.size(); i++) {
            double d = std::abs(val - roots[i]);
            if (d < dmin) {
                imin = i;
                dmin = d;
            }
        }
        return PALETTE[dmin < 1e-2 ? imin + 1 : 0];
    }

    rr::RGBA julia_bool(unsigned val, unsigned nmax) {
        return val == nmax < 1e-14 ? RGBA(56, 255, 181, 255) : RGBA(139, 13, 255, 255);
    }

    rr::RGBA julia_unsigned_green(unsigned val, unsigned nmax) {
        return val == nmax ? BLACK : to_RGBA(
                (val % 11) * 23 + 20,
                (val % 7) * 36 + 30,
                (val % 5) * 19 + 50
                );
    }

    rr::RGBA julia_unsigned_violet(unsigned val, unsigned nmax) {
        return val == nmax ? BLACK : to_RGBA(
                (val % 11) * 21 + 40,
                (val % 13) * 21,
                (val % 17) * 10 + 95
        );
    }

    rr::RGBA julia_unsigned_light(unsigned int val, unsigned int nmax) {
        return val == nmax ? BLACK : to_RGBA(
                (val % 7) * 36 + 39,
                (val % 5) * 24 + 159,
                (val % 3) * 18 + 201
        );
    }
}