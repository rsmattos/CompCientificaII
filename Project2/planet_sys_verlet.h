class Planet_Sys_Verlet:public Planet_Sys{
    private:
        double *u_, *v_;
        double *der_u_;
        double *old_u_, *new_u_;
        // Verlet *solver_;
        int i_;

    public:
        // constructor
        Planet_Sys_Verlet(int N);

        // methods
        void set_solver(struct ODE_set set, struct Params *p);
        void first_step();
        void system_step();

        // destructor
        ~Planet_Sys_Verlet(){
            delete[] u_;
            delete[] old_u_;
            delete[] der_u_;
            delete[] new_u_;
            delete[] v_;
        }
};

inline Planet_Sys_Verlet::Planet_Sys_Verlet(int N){
    u_      = new double[N];
    old_u_  = new double[N];
    der_u_  = new double[N];
    new_u_  = new double[N];
    v_      = new double[N];
    // solver_ = new Verlet(N);
}

inline void Planet_Sys_Verlet::set_solver(struct ODE_set set, struct Params *p){
    p_ = p;

    system_ = set.function;

    days_ = set.initial;
    time_step_ = set.step;
}

inline void Planet_Sys_Verlet::first_step(){
    for(p_->i = 1; p_->i < p_->planets; p_->i++){
        old_u_[0]     = p_->planet[p_->i].get_xx();
        old_u_[1]     = p_->planet[p_->i].get_xy();
        v_[0]         = p_->planet[p_->i].get_vx();
        v_[1]         = p_->planet[p_->i].get_vy();
        
        system_(old_u_, der_u_, days_, p_);

        for(i_ = 0; i_ < 2; i_++){
            u_[i_] = old_u_[i_] + time_step_*v_[i_] + time_step_*time_step_*der_u_[i_]/2.;
        }

        p_->planet[p_->i].new_position(u_[0], u_[1]);
    }

    for(i_ = 1; i_ < p_->planets; i_++){
        p_->planet[i_].update_positions();
    }
}

inline void Planet_Sys_Verlet::system_step(){
    for(p_->i = 1; p_->i < p_->planets; p_->i++){
        u_[0]     = p_->planet[p_->i].get_xx();
        u_[1]     = p_->planet[p_->i].get_xy();
        old_u_[0] = p_->planet[p_->i].get_old_xx();
        old_u_[1] = p_->planet[p_->i].get_old_xy();

        // std::cout << u_[0] << std::endl;
        // std::cout << old_u_[0] << std::endl << std::endl;
        
        for(i_ = 0; i_ < 2; i_++){
            system_(u_, der_u_, days_, p_);

            new_u_[i_] = 2.*u_[i_] - old_u_[i_] + time_step_*time_step_*der_u_[i_];

            // std::cout << old_u_[0] << std::endl;
            // std::cout << u_[0] << std::endl;
            // std::cout << der_u_[0] << std::endl;
            // std::cout << new_u_[0] << std::endl << std::endl;

            v_[i_] = ( new_u_[i_] - old_u_[i_])/(2.*time_step_);
        }

        p_->planet[p_->i].new_position(new_u_[0], new_u_[1]);
        p_->planet[p_->i].new_velocity(v_[0], v_[1]);
    }

    for(i_ = 1; i_ < p_->planets; i_++){
        p_->planet[i_].update_positions();
        p_->planet[i_].update_velocities();
    }

    days_ += time_step_;
}