#include <string>
#include <valarray>
#include <fractal.hpp>

double ftl::lyapunov_exponent(double a, double b, /*const std::string& sequence = "AB",*/ unsigned N) {
    double rn = a;
    double xn = 0.5;
    double res = 0;

    for (unsigned cnt = 0; cnt < N; cnt++) {
        xn = ftl::logistic_map(xn, rn);
        rn = (cnt % 2 > 0) ? a : b;
        res += std::log(std::abs(rn * (1 - 2 * xn)));
    }
    res /= N;

    return res;
}