#include <iostream>
#include <cmath>
#include <random>
#include <limits>

#include <SFML/Graphics.hpp>

#include <noise.hpp>
#include <libs/mathutils.hpp>

const int WIDTH = 512;
const int HEIGHT = 512;

// (quick trick) map a positive real number from (0, range) into the first N integers
int downsample(double value, int n, double range)
{
    return n * value / range;
}

// Update an image with noise
void updateImage(sf::Image& img)
{
    std::random_device r;
    const unsigned int GRID_SIZE = 4;
    ValueNoise2D noise(GRID_SIZE, GRID_SIZE, new Cerp, r(), 3);

    for ( unsigned int i = 0; i < img.getSize().x; i++ )
    {
        for ( unsigned int j = 0; j < img.getSize().y; j++ )
        {   
            // std::cout << "(" << i << ", " << j << ")" << std::endl; 
            auto v = 255.0 * noise((double)i / (double)WIDTH, (double)j / (double)HEIGHT);
            // std::cout << v << std::endl;
            // hard-coded colours for now
            // 77, 38, 0
            // 77, 106, 255
            // unsigned int vp = downsample(v, 10, 255) * (255 / 10);
            // img.setPixel(i, j, sf::Color(77, 100 + downsample(v, 10, 255) * (68 / 10), vp, 255U));
            img.setPixel(i, j, sf::Color(v, v, v, 255U));
        }
    }
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Image img;

    img.create(WIDTH, HEIGHT, sf::Color::Green);

    sf::Texture tex;
    sf::Sprite sp;
    tex.loadFromImage(img);
    sp.setTexture(tex, true);

    PseudoRandom s(100);
    std::cout << s(0, 1) << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Return:
                            updateImage(img);
                            tex.loadFromImage(img);
                            sp.setTexture(tex, true);
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }

        window.clear();
        window.draw(sp);
        window.display();
    }

    return 0;
}