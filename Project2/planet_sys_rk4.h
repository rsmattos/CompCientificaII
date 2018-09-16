class Planet_Sys_RK4{
    private:
        double *u_;
        double E_, V_, K_;
        double days_, time_step_;
        struct Params *p_;
        RK4 *solver_;
        int i_;

    public:
        // constructor
        Planet_Sys_RK4(int N);

        // methods
        void set_solver(struct ODE_set set, struct Params *p);
        void system_step();
        void calc_energy();
        void print_positions();
        void print_energy();
        void print_position_file(std::ofstream *output);
        void print_energy_file(std::ofstream *output);

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

    // RK4 solver(2*set.dimension);
    solver_->set_time(set);
    solver_->set_system(set.function, p_);

    days_ = set.initial;
    time_step_ = set.step;
}

inline void Planet_Sys_RK4::system_step(){
    for(p_->i = 1; p_->i < p_->planets; p_->i++){
        u_[0] = p_->planet[p_->i].get_xx();
        u_[1] = p_->planet[p_->i].get_xy();
        u_[2] = p_->planet[p_->i].get_vx();
        u_[3] = p_->planet[p_->i].get_vy();

        solver_->initial_values(u_);
        solver_->rk4_step();
        solver_->get_variables(u_);

        p_->planet[p_->i].new_position(u_[0], u_[1]);
        p_->planet[p_->i].new_velocity(u_[2], u_[3]);
    }

    for(i_ = 0; i_ < p_->planets; i_++){
        p_->planet[i_].update_positions();
        p_->planet[i_].update_velocities();
    }

    days_ += time_step_;
}

inline void Planet_Sys_RK4::calc_energy(){
    V_ = 0.;
    K_ = 0.;

    for(i_ = 1; i_ < p_->planets; i_++){
        V_ += -p_->G*p_->planet[0].get_mass()*p_->planet[i_].get_mass()/
        sqrt(p_->planet[i_].get_xx()*p_->planet[i_].get_xx() + 
             p_->planet[i_].get_xy()*p_->planet[i_].get_xy());

        K_ += p_->planet[i_].get_mass()*
             (p_->planet[i_].get_vx()*p_->planet[i_].get_vx() + 
              p_->planet[i_].get_vy()*p_->planet[i_].get_vy())/2.;
    }

    E_ = V_ + K_;
}

inline void Planet_Sys_RK4::print_positions(){
    for(i_ = 0; i_ < p_->planets; i_++){
        std::cout << p_->planet[i_].get_name() << '\t' << "(" << p_->planet[i_].get_xx() << ", " << p_->planet[i_].get_xy() << ")" << std::endl;
    }
}

inline void Planet_Sys_RK4::print_energy(){
    std::cout << days_ << '\t' << E_ << std::endl;
}

inline void Planet_Sys_RK4::print_position_file(std::ofstream *output){
    for(i_ = 1; i_ < p_->planets; i_++){
        output[i_] << p_->planet[i_].get_xx() << '\t' << p_->planet[i_].get_xy() << std::endl;
    }
}

inline void Planet_Sys_RK4::print_energy_file(std::ofstream *output){
    output[0] << days_ << '\t' << E_ << std::endl;
}