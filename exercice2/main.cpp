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

    // exemplo 1
    // adiantado
    set.initial = 0.;
    set.final = 5.;
    set.step = .1;
    set.dimension = 1;
    set.method = "forward";
    set.outfile = "./OUTPUT/exemplo_1_adiantado.csv";
    set.function = &exemplo_1;

    double *u = new double[set.dimension];
    double *du = new double[set.dimension];

    u[0] = 1;
    // du[0] = 1;

    solver_to_file(set, u, du);

    // atrasado
    set.method = "backward";
    set.outfile = "./OUTPUT/exemplo_1_atrasado.csv";

    solver_to_file(set, u, du);
//-----------------------------------------------------------
    // exemplo 2
    // adiantado
    set.method = "forward";
    set.outfile = "./OUTPUT/exemplo_2_adiantado.csv";
    set.function = &exemplo_2;

    solver_to_file(set, u, du);

    // atrasado
    set.method = "backward";
    set.outfile = "./OUTPUT/exemplo_2_atrasado.csv";

    solver_to_file(set, u, du);
//------------------------------------------------------------
    // exemplo 3
    // adiantado
    set.final = 7.;
    set.method = "forward";
    set.outfile = "./OUTPUT/exemplo_3_adiantado.csv";
    set.function = &exemplo_3;

    solver_to_file(set, u, du);

    // atrasado
    set.method = "backward";
    set.outfile = "./OUTPUT/exemplo_3_atrasado.csv";

    solver_to_file(set, u, du);

    delete[] u;
    delete[] du;
//-------------------------------------------------------------
    // exemplo 3
    // adiantado
    set.dimension = 2;
    set.method = "forward";
    set.outfile = "./OUTPUT/VanDerPol_adiantado.csv";
    set.function = &VanDerPol;

    double *v = new double[set.dimension];
    double *dv = new double[set.dimension];

    v[0] = 1.; v[1] = 0.;

    solver_to_file(set, v, dv);

    // atrasado
    set.method = "backward";
    set.outfile = "./OUTPUT/VanDerPol_atrasado.csv";

    solver_to_file(set, v, dv);

    delete[] v;
    delete[] dv;
//-------------------------------------------------------------
    
    return 0;
}