#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

struct Params{
    double G;
    class Bodies *planet; 
    int planets;
    int i;
};

typedef void (*func)(double *u, double *du, double t, struct Params *params);

struct ODE_set{
    double initial;
    double final;
    double step;
    int dimension;
    func function;
};

#include "bodies.h"
#include "../exercice2/ODE_solver.h"
#include "function.h"
#include "planetary_system.h"

int main(){
    // setting planetay params
    struct Params p;

    p.G = .1;
    p.planets = 2;

    p.planet = new class Bodies[p.planets];

    // set masses
    p.planet[0].set_mass(64.);
    p.planet[1].set_mass(35.);

    // set initial positions
    p.planet[0].set_position(0., 1.);
    p.planet[1].set_position(1., 0.);

    // set initial velocities
    p.planet[0].set_velocity(2., 0.);
    p.planet[1].set_velocity(0., 0.);

    // setting ODE params
    struct ODE_set set;

    set.initial = 0.;
    set.final = 20.;
    set.step = 2.;
    set.dimension = 2;
    set.function = &planetary2D;

    planetary_system(set, &p);

    delete[] p.planet;
}