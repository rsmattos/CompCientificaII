class RK4:public ODE_solver{
    protected:
        double *new_u_;
        double **kutta_;

    public:
        // constructor
        RK4(int N);

        // methods
        void rk4_step();

        // destructor
        ~RK4(){
            delete[] new_u_;
            delete[] kutta_;
        }
};

inline RK4::RK4(int N):ODE_solver(N){
    new_u_ = new double[N];

    kutta_ = new double*[4];
    for(i_ = 0; i_ < 4; i_++){
        kutta_[i_] = new double[N]; 
    }
}

inline void RK4::rk4_step(){
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