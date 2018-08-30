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

    double *u2 = new double[set.dimension];
    double *du2 = new double[set.dimension];

    u2[0] = 1.; u2[1] = 0.;

    solver_to_file(set, u2, du2);

    // atrasado
    set.method = "backward";
    set.outfile = "./OUTPUT/VanDerPol_atrasado.csv";

    solver_to_file(set, u2, du2);

    delete[] u2;
    delete[] du2;
//-------------------------------------------------------------
    // exemplo 4
    // Crank-Nicolson
    set.initial = 0.;
    set.final = 30;
    set.step = 0.005;
    set.dimension = 3;
    set.method = "cn";
    set.outfile = "./OUTPUT/Lorenz_Crank_Nicolson.csv";
    set.function = &Lorenz;

    double *u3 = new double[set.dimension];
    double *du3 = new double[set.dimension];

    u3[0] = 1; u3[1] = 0.; u3[2] = 0.;
    
    solver_to_file(set, u3, du3);

    // Huen

    u3[0] = 1; u3[1] = 0.1; u3[2] = 0.1;

    set.method = "huen";
    set.outfile = "./OUTPUT/Lorenz_Huen.csv";

    solver_to_file(set, u3, du3);

    delete[] u3;
    delete[] du3;
    
    return 0;
}