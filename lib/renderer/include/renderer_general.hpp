#ifndef RENDERER_GENERAL_HPP
#define RENDERER_GENERAL_HPP
#include <utility>

namespace rr {
    struct RGBA {
        unsigned char R = 0;
        unsigned char G = 0;
        unsigned char B = 0;
        unsigned char A = 255;
    };

    using Cart = std::pair<double, double>;
    using Shape = std::pair<unsigned, unsigned>;
}

#endif