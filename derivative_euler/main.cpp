#include "header.h"

int main(){
    // declaracao da classe de ODE
    ODE_solver solver1(0., 10., .1, 1);

    double *u = new double;
    double *du = new double;

    u[0] = 1;
    du[0] = 1;

    solver1.initial_values(u, du);

    solver1.set_system(exponential1D);

    solver1.print_system();

    solver1.forward_euler_step();

    solver1.print_system();

    solver1.forward_euler_step();

    solver1.print_system();

    delete[] u;
    delete[] du;
    
    return 0;
}