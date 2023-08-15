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
}