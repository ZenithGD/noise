#include <random>

#include <mathutils.hpp>


double TrueRandom::operator()(double lo, double hi) 
{
    return (double)(_rd()) / (double)(_rd.max() - _rd.min()) * (hi - lo) + lo;
}

PseudoRandom::PseudoRandom(int seed) 
    : _rd(seed) {}

double PseudoRandom::operator()(double lo, double hi) 
{
    return (double)(_rd()) / (double)(_rd.max() - _rd.min()) * (hi - lo) + lo;
}

Interpolator1D::~Interpolator1D() {}

double Interpolator2D::eval(double f00, double f10, double f01, double f11, double x, double y)
{
    return _interpolator->eval(_interpolator->eval(f00, f01, y), _interpolator->eval(f10, f11, y), x);
}

double Lerp::eval(double v0, double v1, double t) 
{
    return (1.0 - t) * v0 + t * v1;
}

Lerp::~Lerp() {}

double Cerp::eval(double v0, double v1, double t) 
{
    return t * t * ((2 * t - 3) * v0 + (3 - 2 * t) * v1) + v0;
}

Cerp::~Cerp() {}
