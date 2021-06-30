#include <iostream> 
#include <exception>
#include <vector>
#include <cmath>

#include <noise.hpp>
#include <mathutils.hpp>

ValueNoise2D::ValueNoise2D(const unsigned int m, const unsigned int n, Interpolator1D* im) 
    : _interpolation_method(im), _m(m), _n(n), _grid(m + 1, std::vector<double>(n + 1)) 
{
    std::vector<std::vector<double>> grid(m, std::vector<double>(n));
    for ( unsigned int i = 0; i < m; i++ )
    {
        for ( unsigned int j = 0; j < n; j++ )
        {
            _grid[i][j] = _r(0, 1);
        }
    }
}

double ValueNoise2D::operator()(double x, double y) 
{
    if ( x < 0 || y < 0 || x >= 1 || y >= 1 )
    {
        throw std::runtime_error("The point is not on the unit square");
    }
    else {

        Interpolator2D bcerp(_interpolation_method);
        // 0 <= ygrid < GRID_SIZE
        double ygrid = y * (double)_n;
        int ygrid_tile = ygrid;
        double ygrid_pos = ygrid - floor(ygrid);
        // 0 <= xgrid < GRID_SIZE
        double xgrid = x * (double)_m;
        int xgrid_tile = xgrid;
        double xgrid_pos = xgrid - floor(xgrid);

        return 255.0 * bcerp.eval
        (   
            _grid[xgrid_tile][ygrid_tile], 
            _grid[xgrid_tile + 1][ygrid_tile], 
            _grid[xgrid_tile][ygrid_tile + 1], 
            _grid[xgrid_tile + 1][ygrid_tile + 1],
            xgrid_pos, ygrid_pos
        );
    }
}

ValueNoise2D::~ValueNoise2D()
{
    delete _interpolation_method;   
}
