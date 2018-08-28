// standard headers
#include <cstdio>
#include <iostream>
#include <cmath>

// my headers
#include "ODE_solver.h"
#include "forward_euler.h"
#include "backward_euler.h"
#include "functions_bank.h"

int main(){
    // declaracao da classe de ODE
    ODE_solver solver1(1);

    double *u = new double;
    double *du = new double;

    u[0] = 1;
    // u[1] = 1;
    du[0] = 1;
    // du[1] = 1;
    
    solver1.initial_values(u, du);
    solver1.set_time(0., 10., 0.1);

    solver1.set_system(exponential1D);

    forward_euler(solver1);

    delete[] u;
    delete[] du;
    
    return 0;
}