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
// #include "planetary_system.h"

int main(){
    int i;
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
    set.dimension = 4;
    set.function = &planetary2D;

    // set up solver
    ODE_solver solver(set.dimension);
    solver.set_time(set);
    solver.set_system(set.function, &p);
    solver.set_kutta();

    double *u = new double[set.dimension];

    // calculate new positions and velocities for each planet
    // transform position and velocity in variable vector
    for(p.i = 0; p.i < p.planets; p.i++){
        u[0] = p.planet[p.i].get_xx();
        u[1] = p.planet[p.i].get_xy();
        u[2] = p.planet[p.i].get_vx();
        u[3] = p.planet[p.i].get_vy();

        solver.initial_values(u);
        solver.RK4_step();
        solver.get_variables(u);

        p.planet[p.i].new_position(u[0], u[1]);
        p.planet[p.i].new_velocity(u[2], u[3]);
    }

    std::cout << "primeiro passo" << std::endl;

    for(i = 0; i < p.planets; i++){
        p.planet[i].update_positions();
        p.planet[i].update_velocities();
    
        std::cout << "planet" << i << " (" << p.planet[i].get_xx() << ", " << p.planet[i].get_xy() << ")" << std::endl;
    }

    // calculate new positions and velocities for each planet
    // transform position and velocity in variable vector
    for(p.i = 0; p.i < p.planets; p.i++){
        u[0] = p.planet[p.i].get_xx();
        u[1] = p.planet[p.i].get_xy();
        u[2] = p.planet[p.i].get_vx();
        u[3] = p.planet[p.i].get_vy();

        solver.initial_values(u);
        solver.forward_euler_step();
        solver.get_variables(u);

        p.planet[p.i].new_position(u[0], u[1]);
        p.planet[p.i].new_velocity(u[2], u[3]);
    }

    std::cout << "segundo passo" << std::endl;
    
    for(i = 0; i < p.planets; i++){
        p.planet[i].update_positions();
        p.planet[i].update_velocities();
    
        std::cout << "planet" << i << " (" << p.planet[i].get_xx() << ", " << p.planet[i].get_xy() << ")" << std::endl;
    }

    // update positions and velocities
    delete[] p.planet;
    delete[] u;
}