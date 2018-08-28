#include "header.h"

int main(){
    // declaracao da classe de ODE
    ODE_solver solver1(0., 10., .1, 2);

    double *u = new double[2];
    double *du = new double[2];

    u[0] = 1;
    u[1] = 1;
    du[0] = 1;
    du[1] = 1;
    
    solver1.initial_values(u, du);
    solver1.set_time(0., 10., 0.1);

    solver1.set_system(exponential2D);

    forward_euler(solver1);

    delete[] u;
    delete[] du;
    
    return 0;
}