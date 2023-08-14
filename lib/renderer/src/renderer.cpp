#include "renderer.hpp"

namespace rr {
    void save(std::string name, std::vector<unsigned char> &from, rr::Shape shape) {
        unsigned error = lodepng::encode(name, from, shape.first, shape.second);

        if (error) {
            std::cerr << "LODEPNG: encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
    }
}