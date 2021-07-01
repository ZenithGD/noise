# noise.hpp
A lightweight noise generator library

## Usage
This little library has a class for 1-dimensional and 2-dimensional value noise. You will need a noise object and an interpolator pointer in order to generate the noise function values. Apart from that, you only need to include the math and noise header, and that's all! Here's a quick example:

```C++
...
#include <noise.hpp>
#include <mathutils.hpp>

const int GRID_SIZE = 4;

int main() {

  double x = 0.5, y = 0.5;

  // Create a Noise object with bicubic interpolation and 5 octaves
  Noise noise(GRID_SIZE + 1, GRID_SIZE + 1, new Cerp, rand(), 5);
  
  // Make sure the values for the noise function are between 0 and 1!
  double noiseValue = noise(x, y);
  
  // Use the value
  ...
}
```

A more useful and visually appealing example can be found at `main.cpp`, with its corresponding makefile. To compile the program on Linux, you will need a compiler that supports C++11 and the SFML library. If you don't, you can enter the following command (on Ubuntu/Debian systems):

```
sudo apt-get install libsfml-dev
```

Use the provided makefile for compiling and linking:
```
make
```

The following folder structure will be created in order to organize the generated object files and executables:
```
noise
  |-- main.cpp
  |-- bin
  |    |-- main
  |-- build
  |    |-- *.o
  |-- libs
       |-- *.hpp, *.cpp
```
The executable can be found at the bin folder. To execute it, enter the following command:
```
./bin/main
```

A new window will appear with a solid green background. To generate a noise image, press ENTER. Here's an sample output, a 512 x 512 noise image with bicubic interpolation and 3 octaves:

![imagen](https://user-images.githubusercontent.com/37598162/124051034-f7b8fd00-da1b-11eb-9691-307b756c6e37.png)


