#pragma once

#include <random>
#include <vector>
#include <utility>

// Random number generator
class Random
{
    private:
        std::random_device _rd;

    public:
        /* Pre: 
        *
        */
        double operator()(double lo, double hi);
};

class Interpolator1D
{
    public:
        virtual double eval(double v0, double v1, double t) = 0;
        virtual ~Interpolator1D();
};

class Interpolator2D
{
    private:
        Interpolator1D* _interpolator;
    public:
        Interpolator2D(Interpolator1D* interpolator)
            : _interpolator(interpolator) {}

        double eval(double f00, double f10, double f01, double f11, double x, double y);      
};

class Lerp : public Interpolator1D
{
    /* Pre: -
     * Post: Return a value on the interpolation line between (0, v0) and (1, v1)
     */
    double eval(double v0, double v1, double t) override;
    ~Lerp() override;
};

class Cerp : public Interpolator1D
{
    /* Pre: -
     * Post: Return a value on the cubic interpolator -2x³ + 3x²
     * between (0, v0) and (1, v1)
     */
    double eval(double v0, double v1, double t) override;
    ~Cerp() override;
};