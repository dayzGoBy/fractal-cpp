#include <valarray>
#include "color_mappers.hpp"
#include "renderer_general.hpp"

namespace rr::color_mappers {
    rr::RGBA classic(double val) {

        double r = 0;
        double g = 0;
        double b;
        if (val > 0) {
            b = 255 * val / lambda_max;
        } else {
            r = 255 * (1 - std::pow(val / lambda_min, 1 / 3.0));
            g = 255 * (1 - std::pow(val / lambda_min, 2 / 3.0));
            b = 0;
        }

        return to_RGBA(r, g, b);
    }
}