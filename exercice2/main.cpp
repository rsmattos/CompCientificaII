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
    struct Params params;
    func function;
};

// my headers
#include "functions_bank.h"
#include "ODE_solver.h"
#include "f_euler.h"
#include "b_euler.h"
#include "crank-nicolson.h"
#include "heun.h"
#include "RK4.h"
#include "RK23.h"
#include "solver.h"

int main(){
    struct ODE_set set;

    // exemplo
    set.initial = 0.;
    set.final = 20;
    set.step = 0.1;
    set.dimension = 1;
    set.function = &exemplo_1;

    double *u1 = new double[set.dimension];

    u1[0] = 1.;

    // forward euler
    set.method = "forward_euler";
    set.outfile = "./OUTPUT/test_forward_euler.csv";

    solver_to_file(set, u1);

    // backward euler
    set.method = "backward_euler";
    set.outfile = "./OUTPUT/test_backward_euler.csv";

    solver_to_file(set, u1);

    // cn
    set.method = "cn";
    set.outfile = "./OUTPUT/test_cn.csv";

    solver_to_file(set, u1);

    // heun
    set.method = "heun";
    set.outfile = "./OUTPUT/test_heun.csv";

    solver_to_file(set, u1);

    // rk4
    set.method = "rk4";
    set.outfile = "./OUTPUT/test_rk4.csv";

    solver_to_file(set, u1);

    // forward euler
    set.method = "rk23";
    set.outfile = "./OUTPUT/test_rk23.csv";

    solver_to_file(set, u1);

    delete[] u1;

    return 0;
}