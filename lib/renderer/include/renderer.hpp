#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "lodepng.h"
#include <valarray>
#include <iostream>
#include "fractal.hpp"

namespace rr {
    struct RGBA {
        unsigned char R = 0;
        unsigned char G = 0;
        unsigned char B = 0;
        unsigned char A = 255;
    };

    using Cart = std::pair<double, double>;
    using Shape = std::pair<unsigned, unsigned>;

    // to effectively pass 4 bytes
    RGBA classic(double val);

    void compute_lyapunov(Cart xlim, Cart ylim, unsigned N, Shape shape, std::vector<unsigned char> &to);

    void save(std::string name, std::vector<unsigned char> &from, Shape shape);
}

#endif