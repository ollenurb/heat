#include "surface.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

/*
 * Creates a new surface with the given width and height.
 */
Surface::Surface(unsigned w, unsigned h, double alpha)
{
    this->w = w + 2;
    this->h = h + 2;
    this->alpha = alpha;
    this->dt = 1.0/(4 * alpha);
    temp_points.resize(this->w * this->h);
}

/*
 * Solve the 2D partial differential equation for Heat using the finite
 * difference method.
 */
void Surface::compute_step()
{
    double gamma = alpha * dt;
    for(unsigned i = 1; i < h - 1; i++) {
        for(unsigned j = 1; j < w - 1; j++) {
            getrc(i, j) =
                gamma * (getrc(i + 1, j) + getrc(i - 1, j) +
                (getrc(i, j + 1) + getrc(i, j - 1) -
                (4 * getrc(i, j)))) + getrc(i, j);
        }
    }
}

/*
 * Initialize the plate at a given temperature
 */
void Surface::init(double value)
{
    for(unsigned i = 0; i < temp_points.size(); i++) {
        temp_points[i] = value;
    }
}

/*
 * Get the temperature value at a certain position on the plate
 */
double& Surface::getrc(unsigned r, unsigned c)
{
    if(r > h || c > w) {
        throw std::out_of_range("Attempting to access an invalid index range");
    }
    return temp_points[w * r + c];
}

/*
 * Mostly for debuggin purposes. Just print the temperature values of each
 * point of the plate.
 */
void Surface::print()
{
    std::cout << std::endl;
    for(unsigned i = 0; i < h; i++) {
        for(unsigned j = 0; j < w; j++) {
            std::cout << getrc(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
