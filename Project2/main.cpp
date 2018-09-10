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

    p.G = 4.98211e-7;
    p.planets = 10;

    p.planet = new class Bodies[p.planets];

    // sun properties, it stays outside the position update loop
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // planet properties by planet
    // MERCURY
    p.planet[0].set_name(Mercury);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // VENUS
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // EARTH
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // MARS
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // JUPITER
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // SATURN
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // URANUS
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // NEPTUNE
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // PLUTO
    p.planet[0].set_name(Sun);
    p.planet[0].set_mass();
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);


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