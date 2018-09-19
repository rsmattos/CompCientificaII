#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstring>

#define AU 149597870.700     // km

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
#include "../exercice2/verlet.h"
#include "bodies.h"
#include "planet_sys.h"
#include "planet_sys_rk4.h"
#include "planet_sys_verlet.h"
#include "function.h"
#include "solver.h"
// #include "planetary_system.h"

int main(){
    // setting planetay params
    struct Params p;

    p.G = 4.982174e-10*AU*AU*AU;    // AU3/(kg*day2)
    p.planets = 10;

    p.planet = new class Bodies[p.planets];

    // sun properties, it stays outside the position update loop
    p.planet[0].set_name("Sun");
    p.planet[0].set_mass(1.989e30);
    p.planet[0].set_position(0., 0., 0.);
    p.planet[0].set_velocity(0., 0., 0.);

    // planet properties by planet
    // MERCURY
    p.planet[1].set_name("Mercury");
    p.planet[1].set_mass(3.285e23);
    p.planet[1].set_position(-1.26918062409295e-1, -4.47750819828178e-1, -3.17281414202121e-2);
    p.planet[1].set_velocity( 2.14597548234309e-2, -6.31265972438156e-3, -1.97943813468118e-3);

    // VENUS
    p.planet[2].set_name("Venus");
    p.planet[2].set_mass(4.867e24);
    p.planet[2].set_position(-7.18938244593697e-1, -3.68306028009161e-2,  2.18621410503987e-2);
    p.planet[2].set_velocity( 9.19016637306985e-4, -2.02872083037635e-2, -4.71273188233886e-4);

    // EARTH
    p.planet[3].set_name("Earth");
    p.planet[3].set_mass(5.972e24);
    p.planet[3].set_position(-1.82466362122358e-1,  9.66226129727545e-1,  3.39576595144958e-3);
    p.planet[3].set_velocity( 1.71793603660689e-2, -3.25549750568802e-3, -4.78111024538770e-4);

    // MARS
    p.planet[4].set_name("Mars");
    p.planet[4].set_mass(6.39e23);
    p.planet[4].set_position( 1.39119459867718   , -5.70724722818469e-3,  1.95802300603516e-3);
    p.planet[4].set_velocity( 5.79011526780407e-4,  1.51875155841343e-2,  4.45567579943964e-4);

    // JUPITER
    p.planet[5].set_name("Jupiter");
    p.planet[5].set_mass(1.898e27);
    p.planet[5].set_position( 3.98608854049054   ,  2.96063149041822   ,  2.77925043901118e-2);
    p.planet[5].set_velocity(-4.60443799817529e-3,  6.41787768831458e-3,  9.19511388697671e-6);

    // SATURN
    p.planet[6].set_name("Saturn");
    p.planet[6].set_mass(5.683e26);
    p.planet[6].set_position( 6.37729717199565   ,  6.60695460327579   , -1.45998773495659e-1);
    p.planet[6].set_velocity(-4.31511379100557e-3,  3.86635585175966e-3,  2.25549068246028e-5);

    // URANUS
    p.planet[7].set_name("Uranus");
    p.planet[7].set_mass(8.681e25);
    p.planet[7].set_position( 1.45092025008910e1 , -1.36546370106073e1 ,  2.66757061311420e-2);
    p.planet[7].set_velocity( 2.66294837758073e-3,  2.68705672751516e-3,  6.78162029611345e-5);

    // NEPTUNE
    p.planet[8].set_name("Neptune");
    p.planet[8].set_mass(1.024e26);
    p.planet[8].set_position( 1.69414960422677e1 , -2.49019458134467e1 ,  3.60724496679461e-1);
    p.planet[8].set_velocity( 2.57099524793415e-3,  1.79137641480837e-3, -1.33438959942056e-5);

    // PLUTO
    p.planet[9].set_name("Pluto");
    p.planet[9].set_mass(1.305e22);
    p.planet[9].set_position( -9.86982940132905   , -2.80595370870144e1 ,  5.35614927653737   );
    p.planet[9].set_velocity(  3.05488477990026e-3, -1.51551232104407e-3, -6.45189416882179e-4);


    // setting ODE params
    // using runge kutta 4
    struct ODE_set set;

    set.initial = 0.;
    set.final = 1000.;
    set.step = 2.;
    set.dimension = 3;
    set.function = &planetary3D;

    planetary_system_rk4(set, &p);

    // using verlet
    // set.function = &planetary2D_verlet;

    // planetary_system_verlet(set, &p);

    delete[] p.planet;
}