#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <string>
#include <complex>

namespace ftl {

    inline double logistic_map(double xn, double r) {
        return r * xn * (1 - xn);
    }

    double lyapunov_exponent(double a, double b, const std::string &sequence = "AB", unsigned N = 1e3);

    std::complex<double> newton_method(double x, double y,
                                       std::function<std::complex<double>(std::complex<double>)> &&f,
                                       std::function<std::complex<double>(std::complex<double>)> &&fq,
                                       unsigned N = 1e3,
                                       double eps = 1e-13);

    // return number of iterations made
    unsigned quadratic_julia_set(std::complex<double> z0, std::complex<double> c, unsigned N = 1e3);
}

#endif