// standard headers
#include <cstdio>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <functional>

typedef void (*func)(double *u, double *du, double t);

struct ODE_set{
    double initial;
    double final;
    double step;
    int dimension;

    std::string method;
    std::string outfile;
    func function;
};

// my headers
#include "ODE_solver.h"
// #include "forward_euler.h"
// #include "backward_euler.h"
#include "functions_bank.h"
#include "solver.h"

int main(){
    struct ODE_set set;

    set.initial = 0.;
    set.final = 10.;
    set.step = .1;
    set.dimension = 1;
    set.method = "forward";
    set.outfile = "./OUTPUT/exponential1.csv";
    set.function = &exponential1D;

    double *u = new double[set.dimension];
    double *du = new double[set.dimension];

    u[0] = 1;  u[1] = 1;
    du[0] = 1; du[1] = 1;

    solver_to_file(set, u, du);

    delete[] u;
    delete[] du;
    
    return 0;
}