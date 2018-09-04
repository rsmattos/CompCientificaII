//class to deal with the matrixes
class MatrixClass{
    private:
        double **Aux_A_;
        double **Inv_A_;
        double *A_;
        int N_;

        std::complex<double> *evals_;
        std::complex<double> **S_;
        std::complex<double> **S_inv_;
        std::complex<double> **expA_;

        int i_, j_, k_, s_;
    public:
        // constructors
        MatrixClass(double *Inp_Equs);
        
        // calculate the evalues and evectors
        void set_gsl();    

        void calc_eign();

        double get_det_S();

        void calc_inv_S();

        void liberate_gsl();


        // destructors
        ~MatrixClass(){
            delete[] Aux_A_;
            delete[] A_;
        }
}

inline MatrixClass::MatrixClass(double *Inp_Equs){
    N_ = Inp_Equs[0];

    Aux_A_  = new double*[N_];
    expA_ = new std::complex<double>*[N_];
    S_      = new std::complex<double>*[N_];
    S_inv_  = new std::complex<double>*[N_];
    for(i_ = 0; i_ < N_; i_++){
        Aux_A_[i_]  = new double[N_];
        expA_[i_] = new std::complex<double>[N_];
        S_[i_]      = new std::complex<double>[N_];
        S_inv_[i_]  = new std::complex<double>[N_];
    }

    A_ = new double[N_*N_];

    evals_ = new std::complex<double>[N_];

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            Aux_A_[i][j] = 0.;
        }
    }

    for(i_ = 0; i_ < (N_-1); i_++){
        Aux_A_[i][i+1] = 1.;
        g_[i] = 0;
    }

    g_[N_] = -Inp_Equs[N_]/Inp_Equs[1];

    for(i_ = 0; i_ < N_; i_++){
        Aux_A_[N_][i] = -Inp_Equs[N_-1-i]/Inp_Equs[1];
    }
}

inline void MatrixClass::set_gsl(){
    // create matrix as array
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            A_[i*N_+j] = Aux_A_[i][j];
        }
    }

    gsl_matrix_view m = gsl_matrix_view_array(A_, N_, N_);
    gsl_vector_complex *eval = gsl_vector_complex_alloc(N_);
    gsl_matrix_complex *evec = gsl_matrix_complex_alloc(N_, N_);

    gsl_eigen_nonsymmv_workspace * w = gsl_eigen_nonsymmv_alloc (N_);

    gsl_permutation * p = gsl_permutation_alloc(N_);
    gsl_matrix_complex * S = gsl_matrix_complex_alloc(N_, N_);
    gsl_matrix_complex * Sinv = gsl_matrix_complex_alloc(N_, N_);

    gsl_matrix_view inv = gsl_matrix_view_array(inv_A_);
}

inline void MatrixClass::calc_eign(){
    gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

    gsl_eigen_nonsymmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);

    for (i_ = 0; i < N_; i_++){
        std::real(evals[i_]) = GSL_REAL(gsl_vector_complex_get (eval, i_));
        std::imag(evals[i_]) = GSL_IMAG(gsl_vector_complex_get (eval, i_));

        gsl_vector_complex_view evec_i = gsl_matrix_complex_column (evec, i_);
        
        for (j_ = 0; j_ < N_; ++j){
            gsl_complex z = gsl_vector_complex_get(&evec_i.vector, j_);
            
            std::real(S_[i_][j_]) = GSL_REAL(z); 
            std::imag(S_[i_][j_]) = GSL_IMAG(z);
            
            gsl_matrix_complex_set(S,i_,j_,z);
        }
    }
}

inline double MatrixClass::get_det_S(){
    gsl_complex det = gsl_linalg_complex_LU_det(S,s_);

    return GSL_REAL(det)*GSL_REAL(det) +
           GSL_IMAG(det)*GSL_IMAG(det);
}

inline void MatrixClass::calc_inv_S(){
    gsl_linalg_complex_LU_decomp(S,p,&s_);
    gsl_linalg_complex_LU_invert(S,p,Sinv);

    for (i_ = 0; i < N_; i_++){
        for (j_ = 0; j_ < N_; ++j){
            std::real(S_inv_[i_][j_]) = GSL_REAL(gsl_matrix_complex_get(Sinv,i,j)); 
            std::imag(S_inv_[i_][j_]) = GSL_IMAG(gsl_matrix_complex_get(Sinv,i,j));
        }
    }
}

inline void MatrixClass::liberate_gsl(){
    gsl_vector_complex_free(eval);
    gsl_matrix_complex_free(evec);
    gsl_eigen_nonsymmv_free (w);
    gsl_permutation_free(p);
    gsl_matrix_complex_free(S);
    gsl_matrix_complex_free(Sinv);
}

inline void MatrixClass::calc_inv_A(){
    gsl_linalg_LU_decomp(&m.matrix,p,&s_);
    gsl_linalg_LU_invert(&m.matrix,p,&inv.matrix);

    for (i_ = 0; i < N_; i_++){
        for (j_ = 0; j_ < N_; ++j){
            Inv_A_[i_][j_] = gsl_matrix_get(&inv.matrix,i,j); 
        }
    }
}

inline void MatrixClass::set_gsl(){
    // create matrix as array
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            A_[i*N_+j] = Aux_A_[i][j];
        }
    }

    gsl_matrix_view m = gsl_matrix_view_array(A_, N_, N_);
    gsl_vector_complex *eval = gsl_vector_complex_alloc(N_);
    gsl_matrix_complex *evec = gsl_matrix_complex_alloc(N_, N_);

    gsl_eigen_nonsymmv_workspace * w = gsl_eigen_nonsymmv_alloc (N_);

    gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

    gsl_eigen_nonsymmv_free (w);

    gsl_eigen_nonsymmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);

    gsl_permutation * p = gsl_permutation_alloc(N_);
    gsl_matrix_complex * S = gsl_matrix_complex_alloc(N_, N_);
    gsl_matrix_complex * Sinv = gsl_matrix_complex_alloc(N_, N_);

    for (i_ = 0; i < N_; i_++){
        gsl_vector_complex_view evec_i = gsl_matrix_complex_column (evec, i_);

        std::real(evals[i]) = GSL_REAL(gsl_vector_complex_get (eval, i_));
        std::imag(evals[i]) = GSL_IMAG(gsl_vector_complex_get (eval, i_));
        
        for (j_ = 0; j_ < 4; ++j){
            gsl_complex z = gsl_vector_complex_get(&evec_i.vector, j_);
            
            std::real(evecs[i_][j_]) = GSL_REAL(z); 
            std::imag(evecs[i_][j_]) = GSL_IMAG(z);
            
            gsl_matrix_complex_set(S,i_,j_,z);
        }
    }

    gsl_vector_complex_free(eval);
    gsl_matrix_complex_free(evec);

    gsl_linalg_complex_LU_decomp(S,p,&s);
    gsl_linalg_complex_LU_invert(S,p,Sinv);

    gsl_complex det = gsl_linalg_complex_LU_det(S,s);

    std::complex<double> deter;

    std::real(deter) = GSL_REAL(det); std::imag(deter) = GSL_IMAG(det); 
}

inline void MatrixClass::expA_SAS(double t){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            expA_[i_][j_] = 0.;
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                expA_[i_][j_] += S_[i_][k_]*S_inv_[k_][j_]*exp(t*evals_[k_]);
            }
        }
    }
}

inline void MatrixClass::expA_Taylor(double t){
    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            expA_[i_][j_] = t*Aux_A_[i_][j_];
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        expA_[i_][i_] += 1.;
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                res_[i_][j_] += Aux_A_[i_][k_]*Aux_A_[k_][j_];
            }
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            expA_[i_][j_] += t*t*res_[i_][j_]/2.;
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            temp_res = res_[i_][j_];
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                res_[i_][j_] += temp_res_[i_][k_]*Aux_A_[k_][j_];
            }
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            expA_[i_][j_] += t*t*t*res_[i_][j_]/6.;
        }
    }    
}

inline void MatrixClass::result_vec(double *u0){
    for(i_ = 0; i_ < N_; i_++){
        u_[i_] = 0.;
    }

    for(i_ = 0; i_ < N_; i_++){
        for(k_ = 0; k_ < N_; k_++){
            u_[i_] += expA_[i_][k_]*u0[k];
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            temp_res_[i_][j_] = expA_[i_][j_];
        }
    }

    for(i_ = 0; i_ < N_; i_++){
            temp_res_[i_][i_] -= 1.;
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            res_[i_][j_] = 0.;
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(j_ = 0; j_ < N_; j_++){
            for(k_ = 0; k_ < N_; k_++){
                res_[i_][j_] += Inv_A_[i_][k_]*temp_res_[k_][j_];
            }
        }
    }

    for(i_ = 0; i_ < N_; i_++){
        for(k_ = 0; k_ < N_; k_++){
            u_[i_] += res_[i_][k_]*g_[k];
        }
    }
}

//TODO
testar essa merda e achar os varios erros que certamente vao aparecer
nem todas as variaveis usadas foram declaradas, muito menos alocadas
deletar as paradas tambem