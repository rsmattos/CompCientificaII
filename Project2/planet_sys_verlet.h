class Planet_Sys_Verlet:public Planet_Sys{
    private:
        double *u_, *v_;
        Verlet *solver_;

    public:
        // constructor
        Planet_Sys_Verlet(int N);

        // methods
        void set_solver(struct ODE_set set, struct Params *p);
        void system_step();

        // destructor
        ~Planet_Sys_Verlet(){
            delete[] u_;
            delete[] v_;
        }
};

inline Planet_Sys_Verlet::Planet_Sys_Verlet(int N){
    u_ = new double[N];
    v_ = new double[N];
    solver_ = new Verlet(N);
}

inline void Planet_Sys_Verlet::set_solver(struct ODE_set set, struct Params *p){
    p_ = p;

    solver_->set_time(set);
    solver_->set_system(set.function, p_);

    days_ = set.initial;
    time_step_ = set.step;
}

inline void Planet_Sys_Verlet::system_step(){
    for(p_->i = 1; p_->i < p_->planets; p_->i++){
        u_[0] = p_->planet[p_->i].get_xx();
        u_[1] = p_->planet[p_->i].get_xy();
        v_[0] = p_->planet[p_->i].get_vx();
        v_[1] = p_->planet[p_->i].get_vy();

        solver_->initial_values(u_, v_);
        solver_->verlet_step();
        solver_->get_variables(u_);

        p_->planet[p_->i].new_position(u_[0], u_[1]);
        p_->planet[p_->i].new_velocity(v_[0], v_[1]);
    }

    for(i_ = 0; i_ < p_->planets; i_++){
        p_->planet[i_].update_positions();
        p_->planet[i_].update_velocities();
    }

    days_ += time_step_;
}