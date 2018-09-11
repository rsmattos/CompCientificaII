// class for the system of equaitons
class ODE_solver{
    protected:
        // time params
        double time_;
        double t_limit_;
        double step_size_;
        int step_counter_;
        int method[4];
        int i_;

        // function pointer to the functions being avaliated
        typedef void (*fptr)(double *u, double *du, double t, struct Params *params);
        struct Params *params_;
        fptr system_;

        // variables
        double * u_;
        double * der_u_;
        double * old_u_, * new_u_;           // forward
        double * extra_der_u_;               // cn e huen
        double ** kutta_;
        double rk_error_, rk_tol_;
        int go_back_;
        int dim_;
        int loop_counter_;

    public:
        // constructors
        ODE_solver(int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            step_counter_ = 0;

            method[0] = 0;                // Backward
            method[1] = 0;                // CN
            method[2] = 0;                // Huen
            method[3] = 0;                // RK
        }

        ODE_solver(double t, double t_limit, double step, int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            step_counter_ = 0;

            method[0] = 0;                // Backward
            method[1] = 0;                // CN
            method[2] = 0;                // Huen

            time_ = t;
            t_limit_ = t_limit - step;
            step_size_ = step;
        }

        // void set_backward(){
        //     old_u_ = new double[dim_];
        //     new_u_ = new double[dim_];

        //     method[0] = 1;
        // }

        // void set_cn(){
        //     set_backward();

        //     extra_der_u_ = new double[dim_];

        //     method[1] = 1;
        // }

        // void set_huen(){
        //     extra_der_u_ = new double[dim_];

        //     method[2] = 1;
        // }

        void set_kutta(){
            // set_backward();

            kutta_ = new double*[4];
            for(i_ = 0; i_ < 4; i_++){
                kutta_[i_] = new double[dim_]; 
            }

            method[3] = 1;

            rk_tol_ = 1.e-4;
        }

        // set parameters
        void initial_values(double *u){
            for(i_ = 0; i_ < dim_; i_++){
                u_[i_] = u[i_];
            }
        }

        void set_system(fptr func, struct Params *params){
            system_ = func;
            params_ = params;
        }

        void set_time(double t = 0.0, double t_limit = 10., double step = 0.01){
            time_ = t;
            t_limit_ = t_limit - step;
            step_size_ = step;
            step_counter_ = 0;
        }

        void set_time(struct ODE_set &set){
            time_ = set.initial;
            t_limit_ = set.final - set.step;
            step_size_ = set.step;
            step_counter_ = 0;
        }

        // solvers
        // void cn_step();

        // void huen_step();

        void RK4_step();

        void RK2_3_pre_step();

        void RK2_3_step(double tol);

        void adapt_step_size();

        // return values
        double h(){return step_size_;}

        double t(){return time_;}

        double t_limit(){return t_limit_;}

        void get_variables(double *u);

        int dim(){return dim_;}

        int step_counter(){return step_counter_;}

        // functions to print variables
        void print_system();

        void print_in_time(double);

        void print_in_step(int);

        void file_CSV_print_system(std::ofstream&);

        void file_CSV_print_in_time(double, std::ofstream&);

        void file_CSV_print_in_step(int, std::ofstream&);

        // destructor
        ~ODE_solver(){
            delete[] u_;
            delete[] der_u_;

            if(method[0] == 1){
                delete[] old_u_;
                delete[] new_u_;
            }

            if(method[1] == 1){
                delete[] extra_der_u_;
            }

            if(method[2] == 1){
                delete[] extra_der_u_;
            }

            if(method[3] == 1){
                delete[] kutta_;
            }
        }
};

// inline void ODE_solver::cn_step(){
//     // calculate fn
//     system_(u_, extra_der_u_, time_, params_);

//     // calculate fn+i, already atualizes the steo counter and time
//     backward_euler_step();

//     // calculate the cn step
//     for(i_ = 0; i_ < dim_; i_++){
//         u_[i_] = old_u_[i_] + step_size_*(extra_der_u_[i_] + der_u_[i_]) / 2.;
//     }
// }

// inline void ODE_solver::huen_step(){
//     // calculate fn
//     system_(u_, extra_der_u_, time_, params_);

//     // calculate fn+1
//     time_ = time_ + step_size_;

//     system_(u_, der_u_, time_, params_);

//     // calculate huen step
//     for(i_ = 0; i_ < dim_; i_++){
//         u_[i_] = u_[i_] + step_size_*(extra_der_u_[i_] + der_u_[i_]) / 2.;
//     }

//     step_counter_++;
// }

inline void ODE_solver::RK4_step(){
    // calc first k
    system_(u_, kutta_[0], time_, params_);

    // calc second k
    time_ += step_size_/2.;

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*kutta_[0][i_]/2.;
    }

    system_(new_u_, kutta_[1], time_, params_);

    // calc third k
    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*kutta_[1][i_]/2.;
    }

    system_(new_u_, kutta_[2], time_, params_);

    // calc forth k
    time_ += step_size_/2.;

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*kutta_[2][i_];
    }

    system_(new_u_, kutta_[3], time_, params_);

    // update solution
    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = u_[i_] + step_size_*(kutta_[0][i_] + 2.*kutta_[1][i_] + 2.*kutta_[2][i_] + kutta_[3][i_])/6.;
    }
}

inline void ODE_solver::RK2_3_pre_step(){
    // calc first k
    system_(u_, kutta_[0], time_, params_);

    // calc second k
    time_ += step_size_/2.;

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*kutta_[0][i_]/2.;
    }

    system_(new_u_, kutta_[1], time_, params_);

    // calc third k
    time_ += step_size_/4.;

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + 3*step_size_*kutta_[1][i_]/4.;
    }

    system_(new_u_, kutta_[2], time_, params_);

    // calc forth k
    time_ += step_size_/4.;

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*(2*kutta_[0][i_] + 3.*kutta_[1][i_] + 4.*kutta_[2][i_])/9.;
    }

    system_(new_u_, kutta_[3], time_, params_);

    // update solution
    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = u_[i_] + step_size_*(2.*kutta_[0][i_] + 3.*kutta_[1][i_] + 4.*kutta_[2][i_])/9.;

        // for the higher order solution
        old_u_[i_] = u_[i_] + step_size_*(7.*kutta_[0][i_] + 6.*kutta_[1][i_] + 8.*kutta_[2][i_] + 3.*kutta_[3][i_])/24.;
    }
}

inline void ODE_solver::RK2_3_step(double tol){
    rk_tol_ = tol;

    do{
        RK2_3_pre_step();
        adapt_step_size();
    }while(go_back_ == 1);

    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = new_u_[i_];
    }
}

inline void ODE_solver::adapt_step_size(){
    rk_error_ = -1.;
    
    for(i_ = 0; i_ < dim_; i_++){
        if(fabs(old_u_[i_] - new_u_[i_]) > rk_error_){
            rk_error_ = fabs(old_u_[i_] - new_u_[i_]);
        }
    }

    if(rk_error_ < rk_tol_){
        go_back_ = 0;

        if(rk_error_ < rk_tol_/100.){
            step_size_ = step_size_*2.;
        }
    }
    else{
        step_size_ = step_size_/2.;
        go_back_ = 1;
    }
}

inline void ODE_solver::get_variables(double *u){
    for(i_ = 0; i_ < dim_; i_++){
        u[i_] = u_[i_];
    }
}
inline void ODE_solver::print_system(){
    std::cout << "t = " << time_;
    for(i_ = 0; i_ < dim_; i_++){
        std::cout << " u[" << i_ << "] = " << u_[i_]; 
    }
    std::cout << std::endl;
}

inline void ODE_solver::print_in_time(double t){
    if( remainder(time_, t) < 1.e-5){
        print_system();
    }
}

inline void ODE_solver::print_in_step(int step){
    if( (step_counter_ % step) == 0){
        print_system();
    }
}

inline void ODE_solver::file_CSV_print_system(std::ofstream &output){
    output << time_;
    for(i_ = 0; i_ < dim_; i_++){
        output << "," << u_[i_]; 
    }
    output << std::endl;
}

inline void ODE_solver::file_CSV_print_in_time(double t,std::ofstream &output){
    if( remainder(time_, t) < 1.e-5){
        file_CSV_print_system(output);
    }
}

inline void ODE_solver::file_CSV_print_in_step(int step,std::ofstream &output){
    if( (step_counter_ % step) == 0){
        file_CSV_print_system(output);
    }
}