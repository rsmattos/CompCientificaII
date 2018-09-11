class RK23: public RK4{
    protected:
        double *higher_u_;
        double error_, tol_;
        int go_back_;

    public:
        // constructor
        RK23(int N);

        // methods
        void set_tolerance(double tol);
        void rk23_pre_step();
        void adapt_step_size();
        void rk23_step();

        // destructor
        ~RK23(){
            delete[] higher_u_;
        }
};

inline RK23::RK23(int N):RK4(N){
    higher_u_ = new double[N];
    tol_ = 1.e-4;
}

inline void RK23::set_tolerance(double tol){
    tol_ = tol;
}

inline void RK23::rk23_pre_step(){
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
        higher_u_[i_] = u_[i_] + step_size_*(7.*kutta_[0][i_] + 6.*kutta_[1][i_] + 8.*kutta_[2][i_] + 3.*kutta_[3][i_])/24.;
    }
}

inline void RK23::adapt_step_size(){
    error_ = -1.;
    
    for(i_ = 0; i_ < dim_; i_++){
        if(fabs(higher_u_[i_] - new_u_[i_]) > error_){
            error_ = fabs(higher_u_[i_] - new_u_[i_]);
        }
    }

    if(error_ < tol_){
        go_back_ = 0;

        if(error_ < tol_/100.){
            step_size_ = step_size_*2.;
        }
    }
    else{
        step_size_ = step_size_/2.;
        go_back_ = 1;
    }
}

inline void RK23::rk23_step(){
    do{
        rk23_pre_step();
        adapt_step_size();
    }while(go_back_ == 1);

    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = new_u_[i_];
    }
}