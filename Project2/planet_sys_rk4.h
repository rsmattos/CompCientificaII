class Planet_Sys_RK4:public Planet_Sys{
    private:
        double *u_;
        RK4 *solver_;

    public:
        // constructor
        Planet_Sys_RK4(int N);

        // methods
        void set_solver(struct ODE_set set, struct Params *p);
        void system_step();

        // destructor
        ~Planet_Sys_RK4(){
            delete[] u_;
        }
};

inline Planet_Sys_RK4::Planet_Sys_RK4(int N){
    u_ = new double[2*N];
    solver_ = new RK4(2*N);
}

inline void Planet_Sys_RK4::set_solver(struct ODE_set set, struct Params *p){
    p_ = p;

    solver_->set_time(set);
    solver_->set_system(set.function, p_);

    days_ = set.initial;
    time_step_ = set.step;
}

inline void Planet_Sys_RK4::system_step(){
    for(p_->i = 1; p_->i < p_->planets; p_->i++){
        u_[0] = p_->planet[p_->i].get_xx();
        u_[1] = p_->planet[p_->i].get_xy();
        u_[2] = p_->planet[p_->i].get_xz();    
        u_[3] = p_->planet[p_->i].get_vx();
        u_[4] = p_->planet[p_->i].get_vy();
        u_[5] = p_->planet[p_->i].get_vz();

        solver_->initial_values(u_);
        solver_->rk4_step();
        solver_->get_variables(u_);

        p_->planet[p_->i].new_position(u_[0], u_[1], u_[2]);
        p_->planet[p_->i].new_velocity(u_[3], u_[4], u_[5]);
    }

    for(i_ = 0; i_ < p_->planets; i_++){
        p_->planet[i_].update_positions();
        p_->planet[i_].update_velocities();
    }

    days_ += time_step_;
}