void sys_solver(){
    // dimensao da matriz
    int dim = 2;
    int i;
    
    
    MatrixClass mat(dim);

    double **A;

    A = new double*[dim];
    for(i = 0; i < dim; i++){
        A[i] = new double[dim];
    }

    A[0][0] = 5.;
    A[0][1] = 5.;
    A[1][0] = 5.;
    A[1][1] = 5.;
    
    mat.get_A_(A);
}