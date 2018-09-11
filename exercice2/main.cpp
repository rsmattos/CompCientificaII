// standard headers
#include <cstdio>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

struct Params{
};

typedef void (*func)(double *u, double *du, double t, struct Params *params);

struct ODE_set{
    double initial;
    double final;
    double step;
    int dimension;

    double rk_tol;

    std::string method;
    std::string outfile;
    struct Params *params;
    func function;
};

// my headers
#include "functions_bank.h"
#include "ODE_solver.h"
#include "f_euler.h"
#include "b_euler.h"
#include "crank-nicolson.h"
#include "heun.h"
#include "solver.h"

int main(){
    struct ODE_set set;
    set.params = new Params;

    // exemplo
    // backward euler
    set.initial = 0.;
    set.final = 20;
    set.step = 0.1;
    set.dimension = 1;
    set.method = "heun";
    set.outfile = "./OUTPUT/test_heun.csv";
    set.function = &exemplo_1;

    double *u1 = new double[set.dimension];

    u1[0] = 1.;
    
    solver_to_file(set, u1);

    // // referencia
    // // backward euler
    // set.method = "backward";
    // set.outfile = "./OUTPUT/ref_backward.csv";

    // solver_to_file(set, u1);

    delete[] u1;
    delete[] set.params;

    return 0;
}