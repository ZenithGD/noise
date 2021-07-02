#pragma once

#include <vector>
#include <cmath>
#include <mathutils.hpp>

class ValueNoise2D
{
    protected:

        Interpolator1D* _interpolation_method;
        int _seed;
        int _octaves;
        unsigned int _m;
        unsigned int _n;
        std::vector<std::vector<std::vector<double>>> _grid;

        void generateGrid(int octave);

        void computeNoise(double x, double y, double& value);

    public:
        /* Pre: -
         * Post: Generate a random (M + 1) x (N - 1) grid with numbers in [0, 1]
         */
        ValueNoise2D(const unsigned int m, const unsigned int n, Interpolator1D* im, int seed, int octaves);

        double operator()(double x, double y);
    
        ~ValueNoise2D();
};
