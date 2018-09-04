//class to deal with the matrixes
class MatrixClass{
    private:
        // matrix diension
        int N_;
        // input matrix for the system
        double **Aux_A_;
        // matrix A to power n
        double **N_A_;
        // Taylor sum term
        double **Tay_;
        // Taylor sum term times transpose
        double **Tay_sqr_;
        // real value of eignval
        double eival;
        // exp A matrix
        double **exp_A_;

        // transoformar matriz em vetor pro gsl
        double *A_;

        int i_, j_, k_, s_;

    public:
        // constructors
        MatrixClass(int &N);

        // pegar valores de A
        void get_A_(double **Mat);
        
        // inicializar expA
        void init_expA();

        // calcular A^n

        // calcular termo

        // calcular termo com transposta

        // inicializar gsl

        // calcular autovalor mais alto

        // adicionar termo ao expA

        // destructors
        ~MatrixClass(){
            delete[] Aux_A_;
            delete[] N_A_;
            delete[] Tay_;
            delete[] Tay_sqr_;
            delete[] exp_A_;
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

inline MatrixClass::MatrixClass(int &N){
    N_ = N;

    Aux_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        Aux_A_[i_] = new double[N];
    }

    N_A_ = new double*[N];
    for(i_ = 0; i_ < N; i_++){
        N_A_[i_] = new double[N];
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
}

inline void MatrixClass::get_A_(double **Mat){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            Aux_A_[i_][j_] = Mat[i_][j_];
        }
    }
}

inline void MatrixClass::init_expA()[
    init_zero(exp_A_,N_);

    // add the identity
    for(i_ = 0; i_ < N_; i_++){
        exp_A_[i_][i_] = 1.;
    }

    // add the first term
]