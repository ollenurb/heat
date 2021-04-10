#ifndef SURFACE_H
#define SURFACE_H

#include <vector>

using namespace std;

/* Represents the 2D surface where the simulation on heat will run.
 * Each point on the surface has its corresponding temperature.
 * Data of the 2D temperature function are represented with a matrix
 * called temp_points.
 */
class Surface {
    private:
        vector<double> temp_points;
        unsigned w, h;
        double dxy, dt;
        double alpha;

    public:
        Surface(unsigned, unsigned);
        Surface(unsigned, unsigned, double);
        void compute_step();
        void init(double);
        void print();
        double& getrc(unsigned, unsigned);
};

#endif
