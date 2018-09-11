class Heun: public ODE_solver{
    protected:
        double *extra_der_u_;

    public:
        // constructor
        Heun(int N);

        // methods
        void heun_step();
        // destructor
        ~Heun(){
            delete[] extra_der_u_;
        }
};

inline Heun::Heun(int N):ODE_solver(N){
    extra_der_u_ = new double[N];
}

inline void Heun::heun_step(){
    // calculate fn
    system_(u_, extra_der_u_, time_, params_);

    // calculate fn+1
    time_ = time_ + step_size_;

    system_(u_, der_u_, time_, params_);

    // calculate huen step
    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = u_[i_] + step_size_*(extra_der_u_[i_] + der_u_[i_]) / 2.;
    }

    step_counter_++;
}