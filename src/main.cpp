#include <iostream>
#include <vector>
#include "renderer.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "the only arg is filename" << std::endl;
    }

    std::vector<unsigned char> image;
    rr::Shape shape = {1000, 1000};

    rr::compute_lyapunov({3.81, 3.87}, {3.81, 3.87}, 1000, shape, image);
    rr::save(argv[1], image, shape);
}