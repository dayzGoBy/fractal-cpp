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
    Buffer compute_pixels(Cart xlim, Cart ylim, Shape shape, std::function<rr::RGBA(double, double)> &&f,
                          unsigned nthreads = 10);

    void save(std::string name, std::vector<unsigned char> &from, Shape shape);
}

#endif