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
#include "../exercice2/RK4.h"
#include "../exercice2/verlet.h"
#include "function.h"
#include "planetary_system.h"

int main(){
    // setting planetay params
    struct Params p;

    p.G = 4.98211e-7;
    p.planets = 10;

    p.planet = new class Bodies[p.planets];

    // sun properties, it stays outside the position update loop
    p.planet[0].set_name("Sun");
    p.planet[0].set_mass(1.989e6);
    p.planet[0].set_position(600., 600.);
    p.planet[0].set_velocity(0., 0.);

    // planet properties by planet
    // MERCURY
    p.planet[1].set_name("Mercury");
    p.planet[1].set_mass(.33);
    p.planet[1].set_position(600., 594.21);
    p.planet[1].set_velocity(0.26371969859, 0.0362423611009);

    // VENUS
    p.planet[2].set_name("Venus");
    p.planet[2].set_mass(4.87);
    p.planet[2].set_position(600., 589.18);
    p.planet[2].set_velocity(0.841810004715, 0.240343746883);

    // EARTH
    p.planet[3].set_name("Earth");
    p.planet[3].set_mass(5.97);
    p.planet[3].set_position(600., 749.6);
    p.planet[3].set_velocity(-0.177759577499, -0.0754366450966);

    // MARS
    p.planet[4].set_name("Mars");
    p.planet[4].set_mass(.642);
    p.planet[4].set_position(600., 372.0);
    p.planet[4].set_velocity(0.0536458655351, -0.0754366450966);

    // JUPITER
    p.planet[5].set_name("Jupiter");
    p.planet[5].set_mass(1898.);
    p.planet[5].set_position(600., 178.6);
    p.planet[5].set_velocity(1.96697778225, -0.485436372127);

    // SATURN
    p.planet[6].set_name("Saturn");
    p.planet[6].set_mass(568.);
    p.planet[6].set_position(833.5, 1190.0);
    p.planet[6].set_velocity(0.84539364043, -0.244297836619);

    // URANUS
    p.planet[7].set_name("Uranus");
    p.planet[7].set_mass(86.8);
    p.planet[7].set_position(874.13, 50.0);
    p.planet[7].set_velocity(0.373091224153, -0.244297836619);

    // NEPTUNE
    p.planet[8].set_name("Neptune");
    p.planet[8].set_mass(102.0);
    p.planet[8].set_position(144.45, 10.0);
    p.planet[8].set_velocity(0.418646550354, -0.159208435589);

    // PLUTO
    p.planet[9].set_name("Pluto");
    p.planet[9].set_mass(.0146);
    p.planet[9].set_position(590.0,-100.0);
    p.planet[9].set_velocity(0.00568501382124, 3.47457436434e-05);


    // setting ODE params
    // using runge kutta 4
    struct ODE_set set;

    set.initial = 0.;
    set.final = 20.;
    set.step = 2.;
    set.dimension = 2;
    set.function = &planetary2D;

    planetary_system(set, &p);

    std::cout << "Verlet" << std::endl;

    // using verlet
    set.function = &planetary2D_verlet;

    planetary_system_verlet(set, &p);

    delete[] p.planet;
}