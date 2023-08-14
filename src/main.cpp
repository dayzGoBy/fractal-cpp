#include <iostream>
#include <vector>
#include "renderer.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "the only arg is filename" << std::endl;
    }
    rr::Shape shape = {1000, 1000};
    std::vector<unsigned char> image = rr::compute_pixels({3.81, 3.87}, {3.81, 3.87},
                                                          shape, ftl::lyapunov_exponent, 1000);
    rr::save(argv[1], image, shape);
}