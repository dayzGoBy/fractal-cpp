#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "lodepng.h"
#include <valarray>
#include <iostream>
#include "fractal.hpp"
#include "renderer_general.hpp"

namespace rr {
    void compute_lyapunov(Cart xlim, Cart ylim, unsigned N, Shape shape, std::vector<unsigned char> &to);

    void save(std::string name, std::vector<unsigned char> &from, Shape shape);

    namespace color_mappers {
        RGBA classic(double val);
    }
}

#endif