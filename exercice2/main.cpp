// standard headers
#include <cstdio>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

typedef void (*func)(double *u, double *du, double t);

struct ODE_set{
    double initial;
    double final;
    double step;
    int dimension;

    double rk_tol;

    std::string method;
    std::string outfile;
    func function;
};

// my headers
#include "ODE_solver.h"
#include "functions_bank.h"
#include "solver.h"

int main(){
    struct ODE_set set;

    // execicio 1
    // Runge-Kutta 4
    set.initial = 0.;
    set.final = 20;
    set.step = 0.1;
    set.dimension = 2;
    set.method = "rk4";
    set.outfile = "./OUTPUT/exercicio1_Runge_Kutta_4.csv";
    set.function = &exercicio_1;

    double *u1 = new double[set.dimension];

    u1[0] = 2; u1[1] = 1.;
    
    solver_to_file(set, u1);

    delete[] u1;

    // execicio 2
    // Runge-Kutta 2/3
    set.initial = 0.;
    set.final = 20;
    set.step = 0.1;
    set.dimension = 1;
    set.rk_tol = 1.e-3;
    set.method = "rk23";
    set.outfile = "./OUTPUT/exercicio2_RK_23_tol_3.csv";
    set.function = &exercicio_2;

    double *u2 = new double[set.dimension];

    u2[0] = 1.;
    
    solver_to_file(set, u2);

    delete[] u2;

    // execicio 3
    // Runge-Kutta 2/3
    set.initial = 0.;
    set.final = 20;
    set.step = 0.1;
    set.dimension = 1;
    set.rk_tol = 1.e-4;
    set.method = "rk23";
    set.outfile = "./OUTPUT/exercicio2_RK_23_tol_4.csv";
    set.function = &exercicio_2;

    double *u3 = new double[set.dimension];

    u3[0] = 1.;
    
    solver_to_file(set, u3);

    delete[] u3;

    return 0;
}