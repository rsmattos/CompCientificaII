class Verlet:public ODE_solver{
    protected:
        double *old_u_;
        double *new_u_;
        double *v_;

    public:
        // constructor
        Verlet(int N);

        // methods
        void initial_values(double *r, double *v);
        void calculate_position();
        void calculate_velocity();
        void update_positions();
        void verlet_step();

        // destructor
        ~Verlet(){
            delete[] old_u_;
            delete[] new_u_;
            delete[] v_;
        }
};

inline Verlet::Verlet(int N):ODE_solver(N){
    old_u_ = new double[N];
    new_u_ = new double[N];
    v_ = new double[N];
}

inline void Verlet::initial_values(double *r, double *v){
    for(i_ = 0; i_ < dim_; i_++){
        old_u_[i_] = r[i_];
        v_[i_] = v[i_];
    }

    system_(old_u_, der_u_, time_, params_);

    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = old_u_[i_] + step_size_*v_[i_] + step_size_*step_size_*der_u_[i_]/2.;
    }

    step_counter_ = 1;
}

inline void Verlet::calculate_position(){
    system_(u_, der_u_, time_, params_);

    for(i_ = 0; i_ < dim_; i_++){
        new_u_[i_] = 2.*u_[i_] - old_u_[i_] + step_size_*step_size_*der_u_[i_];
    }
}

inline void Verlet::calculate_velocity(){
    for(i_ = 0; i_ < dim_; i_++){
        v_[i_] = ( new_u_[i_] - old_u_[i_])/(2.*step_size_);
    }
}

inline void Verlet::update_positions(){
    for(i_ = 0; i_ < dim_; i_++){
        old_u_[i_] = u_[i_];
        u_[i_] = new_u_[i_];
    }
}

inline void Verlet::verlet_step(){
    calculate_position();
    calculate_velocity();
    update_positions();
}