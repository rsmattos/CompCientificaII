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

    A[0][0] = -1./3.;
    A[0][1] = 1.;
    A[1][0] = -2.;
    A[1][1] = -.5;
    
    mat.set_A(A);

    mat.init_expA(t);

    mat.print_expA();

    mat.step_AN();

    mat.print_AN();

    mat.update_term(t);

    mat.print_Tay_term();

    mat.update_expA();

    mat.print_expA();

    mat.calc_Tay_sqr();

    mat.print_Tay_sqr();

    mat.calc_max_eval();

    mat.print_eval();

    double eval = mat.get_eval();

    while(eval > .1){
        mat.step_AN();

        mat.print_AN();

        mat.update_term(t);

        mat.print_Tay_term();

        mat.update_expA();

        mat.print_expA();

        mat.calc_Tay_sqr();

        mat.print_Tay_sqr();

        mat.calc_max_eval();

        mat.print_eval();

        eval = mat.get_eval();

        std::cout << std::endl;
    }

}