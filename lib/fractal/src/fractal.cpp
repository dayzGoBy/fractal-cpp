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

std::complex<double>
ftl::newton_method(double x, double y, std::function<std::complex<double>(std::complex<double>)> &&f,
                   std::function<std::complex<double>(std::complex<double>)> &&fq, unsigned N, double eps) {
    std::complex<double> zprev = {x, y};
    std::complex<double> zn = zprev - f(zprev) / fq(zprev);

    for (unsigned cnt = 0; cnt < N && std::abs(zn - zprev) > eps; cnt++) {
        zprev = zn;
        zn = zn - f(zn) / fq(zn);
    }

    return zn;
}
