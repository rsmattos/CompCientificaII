//class to deal with the matrixes
class MatrixClass{
    private:
        // matrix diension
        int N_;
        // order of the Taylor aproximation
        int ord_;
        // contant multiplying the Taylor term
        double cons_;
        // Taylor approximation tolerance
        double tol_;

        // input matrix for the system
        double **Aux_A_;
        // matrix A to power n
        double **N_A_;
        double **Aux_N_A_;
        // Taylor sum term
        double **Tay_;
        // Taylor sum term times transpose
        double **Tay_sqr_;
        // real value of eignval
        double eval_;
        // exp A matrix
        double **exp_A_;
        // initial value and answer
        double *u0_;
        double *ut_;

        // gsl
        double *A_;

        int i_, j_, k_;

    public:
        // individual steps----------------------------------
        // constructors
        MatrixClass(int N);

        // pegar valores de A
        void set_A(double **Mat);

        // determine Taylor convergence limit
        void set_tol(double tol);

        // initial value for the problem
        void set_init_value(double *u0);
        
        // inicializar expA
        void init_expA(double t);
        void print_expA();

        // calculate A^n
        void step_AN();
        void print_AN();

        // calculate the new Taylor term
        void update_term(double t);
        void print_Tay_term();

        // calculate Taylor term squared
        void calc_Tay_sqr();
        void print_Tay_sqr();

        // calculate the highest eigenvalue
        void calc_max_eval();
        void print_eval();
        double get_eval(){return eval_;}

        // adicionar termo ao expA
        void update_expA();

        // calculate the final expA for t
        void calc_expA(double t);

        // calculate the solution at time t
        void calc_ut();
        void calc_ut(double t);
        void print_ut();
        void print_ut(double t);

        // destructors
        ~MatrixClass(){
            delete[] Aux_A_;
            delete[] N_A_;
            delete[] Aux_N_A_;
            delete[] Tay_;
            delete[] Tay_sqr_;
            delete[] exp_A_;
            delete[] u0_;
            delete[] ut_;
            delete[] A_;
        }
};

void init_zero(double **Mat, int &N){
    int i, j;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            Mat[i][j] = 0.;
        }
    }
}

inline MatrixClass::MatrixClass(int N){
    N_ = N;

    Aux_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        Aux_A_[i_] = new double[N];
    }

    N_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        N_A_[i_] = new double[N];
    }

    Aux_N_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        Aux_N_A_[i_] = new double[N];
    }

    Tay_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        Tay_[i_] = new double[N];
    }

    Tay_sqr_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        Tay_sqr_[i_] = new double[N];
    }

    exp_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        exp_A_[i_] = new double[N];
    }
    
    u0_ = new double[N];

    ut_ = new double[N];

    // gsl
    A_ = new double[N*N];
}

inline void MatrixClass::set_A(double **Mat){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            Aux_A_[i_][j_] = Mat[i_][j_];
        }
    }
}

inline void MatrixClass::set_tol(double tol){
    tol_ = tol;
}

inline void MatrixClass::set_init_value(double *u0){
    for(i_ = 0; i_ < N_; i_++){
        u0_[i_] = u0[i_];
    }
}

inline void MatrixClass::init_expA(double t){
    init_zero(exp_A_,N_);

    // add the identity
    for(i_ = 0; i_ < N_; i_++){
        exp_A_[i_][i_] = 1.;
    }

    // initialize the constant
    cons_ = t;
    // add the first term
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            exp_A_[i_][j_] += Aux_A_[i_][j_];
        }
    }

    // save first auxiliar function
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            N_A_[i_][j_] = Aux_A_[i_][j_];
        }
    }

    // set the order of the approximation
    ord_ = 1;


}

inline void MatrixClass::print_expA(){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            std::cout << "expA" << i_ << j_ << " = " << exp_A_[i_][j_] << std::endl;
        }
    }
}

inline void MatrixClass::step_AN(){
    // save the last AN
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            Aux_N_A_[i_][j_] = N_A_[i_][j_];
        }
    }

    // product AN*A for A(N+1)
    init_zero(N_A_, N_);

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                N_A_[i_][j_] += Aux_N_A_[i_][k_]*Aux_A_[k_][j_];
            }
        }
    }
}

inline void MatrixClass::print_AN(){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            std::cout << "AN" << i_ << j_ << " = " << N_A_[i_][j_] << std::endl;
        }
    }
}

inline void MatrixClass::update_term(double t){
    // update the order of the approximation
    ord_++;

    // update the constant multiplying the matrix
    cons_ *= t/ord_;

    // calculate the new term
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            Tay_[i_][j_] = cons_*N_A_[i_][j_];
        }
    }
}

inline void MatrixClass::print_Tay_term(){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            std::cout << "Taylor term" << i_ << j_ << " = " << Tay_[i_][j_] << std::endl;
        }
    }
}

inline void MatrixClass::update_expA(){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            exp_A_[i_][j_] += Tay_[i_][j_];
        }
    }
}

inline void MatrixClass::calc_Tay_sqr(){
    init_zero(Tay_sqr_, N_);

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                Tay_sqr_[i_][j_] += Tay_[k_][i_]*Tay_[k_][j_];
            }
        }
    }
}

inline void MatrixClass::print_Tay_sqr(){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            std::cout << "Taylor term squared" << i_ << j_ << " = " << Tay_sqr_[i_][j_] << std::endl;
        }
    }
}

inline void MatrixClass::calc_max_eval(){
    // create the matrix in the format red by gsl
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            A_[i_*N_+j_] = Tay_sqr_[i_][j_];
        }
    }

    gsl_matrix_view m = gsl_matrix_view_array(A_, N_, N_);
    gsl_vector_complex *eval = gsl_vector_complex_alloc(N_);
    gsl_matrix_complex *evec = gsl_matrix_complex_alloc(N_, N_);

    gsl_eigen_nonsymmv_workspace * w = gsl_eigen_nonsymmv_alloc (N_);

    gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

    gsl_eigen_nonsymmv_free (w);

    gsl_eigen_nonsymmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);

    eval_ = GSL_REAL(gsl_vector_complex_get(eval,0));

    gsl_vector_complex_free(eval);
    gsl_matrix_complex_free(evec);
}

inline void MatrixClass::print_eval(){
    std::cout << "maximum eigenvalue" << eval_ << std::endl;
}

inline void MatrixClass::calc_expA(double t){
    init_expA(t);

    do{
        step_AN();

        update_term(t);

        update_expA();

        calc_Tay_sqr();

        calc_max_eval();
    }while(eval_ > tol_);
}

inline void MatrixClass::calc_ut(){
    for(i_ = 0; i_ < N_; i_++){
        ut_[i_] = 0.;
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            ut_[i_] += exp_A_[i_][j_]*u0_[j_];
        }
    }
}

inline void MatrixClass::calc_ut(double t){
    calc_expA(t);

    calc_ut();
}

inline void MatrixClass::print_ut(){
    for(i_ = 0; i_ < N_; i_++){
        std::cout << '\t' << ut_[i_];
    }

    std::cout << std::endl;
}

inline void MatrixClass::print_ut(double t){
    std::cout << t;

    print_ut();
}