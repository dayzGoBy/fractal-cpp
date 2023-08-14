#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <string>

namespace ftl {

    inline double logistic_map(double xn, double r) {
        return r * xn * (1 - xn);
    }

    double lyapunov_exponent(double a, double b, /*const std::string& sequence = "AB",*/ unsigned N);

}

#endif