#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
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

#include "../exercice2/ODE_solver.h"
#include "../exercice2/RK4.h"
#include "bodies.h"
#include "planet_sys.h"
#include "planet_sys_rk4.h"
#include "planet_sys_verlet.h"
#include "function.h"
#include "solver.h"
// #include "planetary_system.h"

void set_initial_values(struct Params p){
    // sun properties, it stays outside the position update loop
    p.planet[0].set_name("Sun");
    p.planet[0].set_mass(1.989e6);              // Skg
    p.planet[0].set_position(600., 600.);       // pixel
    p.planet[0].set_velocity(0., 0.);           // pixel/day

    // planet properties by planet
    // MERCURY
    p.planet[1].set_name("Mercury");
    p.planet[1].set_mass(.33);
    p.planet[1].set_position(600., 594.21);
    p.planet[1].set_velocity(0.3, 0.0);

    // VENUS
    p.planet[2].set_name("Venus");
    p.planet[2].set_mass(4.87);
    p.planet[2].set_position(600., 589.18);
    p.planet[2].set_velocity(0.3, 0.0);

    // EARTH
    p.planet[3].set_name("Earth");
    p.planet[3].set_mass(5.97);
    p.planet[3].set_position(600., 800.);
    p.planet[3].set_velocity(0.08, 0.0);

    // MARS
    p.planet[4].set_name("Mars");
    p.planet[4].set_mass(.642);
    p.planet[4].set_position(600., 372.0);
    p.planet[4].set_velocity(0.0536458655351, 0.0);

    // JUPITER
    p.planet[5].set_name("Jupiter");
    p.planet[5].set_mass(1898.);
    p.planet[5].set_position(600., 178.6);
    p.planet[5].set_velocity(.05, 0.0);

    // SATURN
    p.planet[6].set_name("Saturn");
    p.planet[6].set_mass(568.);
    p.planet[6].set_position(833.5, 1190.0);
    p.planet[6].set_velocity(0.01, -0.004);

    // URANUS
    p.planet[7].set_name("Uranus");
    p.planet[7].set_mass(86.8);
    p.planet[7].set_position(874.13, 50.0);
    p.planet[7].set_velocity(0.04, -0.0);

    // NEPTUNE
    p.planet[8].set_name("Neptune");
    p.planet[8].set_mass(102.0);
    p.planet[8].set_position(144.45, 10.0);
    p.planet[8].set_velocity(0.01, -0.001);

    // PLUTO
    p.planet[9].set_name("Pluto");
    p.planet[9].set_mass(.0146);
    p.planet[9].set_position(590.0,-100.0);
    p.planet[9].set_velocity(0.00568501382124, 3.47457436434e-05);
}

int main(){
    // setting planetay params
    struct Params p;

    p.G = 4.98211e-7;    // pixel3/(Skg*day2)
    p.planets = 10;

    p.planet = new class Bodies[p.planets];

    // setting ODE params
    // using runge kutta 4
    struct ODE_set set;

    set.initial = 0.;
    set.final = 100000.;
    set.step = 2.;
    set.dimension = 2;
    set.function = &planetary2D;

    set_initial_values(p);

    planetary_system_rk4(set, &p);

    // using verlet
    set_initial_values(p);

    set.function = &planetary2D_verlet;

    planetary_system_verlet(set, &p);

    delete[] p.planet;
}