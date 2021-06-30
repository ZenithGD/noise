#pragma once

#include <vector>
#include <cmath>
#include <mathutils.hpp>

class ValueNoise2D
{
    protected:
        Interpolator1D* _interpolation_method;
        Random _r;
        unsigned int _m;
        unsigned int _n;
        std::vector<std::vector<double>> _grid;
    public:
        /* Pre: -
         * Post: Generate a random (M + 1) x (N - 1) grid with numbers in [0, 1]
         */
        ValueNoise2D(const unsigned int m, const unsigned int n, Interpolator1D* im);

        double operator()(double x, double y);
    
        ~ValueNoise2D();
};
