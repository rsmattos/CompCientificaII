void sys_solver(){
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

    mat.calc_expA(t);

    mat.print_expA();

    mat.calc_ut();
    
    mat.print_ut(t);
}