#include <stdio.h>
#include <iostream>
#include <fstream>
#include <complex>

#include <gsl/gsl_eigen.h>

#include "setMat.h"

int main(){
    // dimensao da matriz
    int dim = 2;
    int i;
    double t = 5.;
    
    MatrixClass mat(dim);

    double **A;

    A = new double*[dim];
    for(i = 0; i < dim; i++){
        A[i] = new double[dim];
    }

    double *u0 = new double[dim];

    A[0][0] = -1./3.;
    A[0][1] = 1.;
    A[1][0] = -2.;
    A[1][1] = -.5;

    u0[0] = 1.;
    u0[1] = 1.;
    
    mat.set_A(A);

    mat.set_init_value(u0);

    mat.set_tol(.1);

    std::ofstream output("project1.csv");

    output << "t";
    for(i = 0; i < dim; i++){
        output << ",u[" << i << "]"; 
    }
    output << std::endl;


    for(i = 0; i < 20; i++){
        t++;

        mat.calc_expA(t);

        mat.calc_ut();
        
        mat.file_CSV_print_system(t, output);
    }

    output.close();
}