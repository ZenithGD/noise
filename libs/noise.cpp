#include <iostream> 
#include <exception>
#include <vector>
#include <cmath>

#include <noise.hpp>
#include <mathutils.hpp>

ValueNoise2D::ValueNoise2D(const unsigned int m, const unsigned int n, Interpolator1D* im, int seed, int octaves) 
    : _interpolation_method(im), _seed(seed), _octaves(octaves), _m(m), _n(n), _grid(octaves, 
                                                                  std::vector<std::vector<double>>(m + 1, 
                                                                                                   std::vector<double>(n + 1))) 
{
    for ( int i = 0; i < _octaves; i++ )
    {
        generateGrid(i);
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

        double value = 0.0;
        
        for (int i = 0; i < _octaves; i++)
        {
            // std::cout << "Octave " << i << "|" << _grid[i][xgrid_tile][ygrid_tile] << std::endl;

            value += bcerp.eval
            (   
                _grid[i][xgrid_tile][ygrid_tile], 
                _grid[i][xgrid_tile + 1][ygrid_tile], 
                _grid[i][xgrid_tile][ygrid_tile + 1], 
                _grid[i][xgrid_tile + 1][ygrid_tile + 1],
                xgrid_pos, ygrid_pos
            );
        }

        // std::cout << value << std::endl;
        return value / (double)_octaves;
    }
}

ValueNoise2D::~ValueNoise2D()
{
    delete _interpolation_method;   
}

void ValueNoise2D::generateGrid(int octave) 
{
    PseudoRandom _r(_seed + octave);
    for ( unsigned int i = 0; i <= _m; i++ )
    {
        for ( unsigned int j = 0; j <= _n; j++ )
        {
            _grid[octave][i][j] = _r(0, 1);
        }
    }
}
