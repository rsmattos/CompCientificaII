class Planet_Sys{
    protected:
        double E_, V_, K_;
        double days_, time_step_;
        struct Params *p_;
        int i_;

    public:
        // constructor

        // methods
        void set_solver(struct ODE_set set, struct Params *p);
        void calc_energy();
        void print_positions();
        void print_energy();
        void print_position_file(std::ofstream *output);
        void print_pos_vel_file(std::ofstream *output);
        void print_energy_file(std::ofstream *output);

        // destructor
};

inline void Planet_Sys::calc_energy(){
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

inline void Planet_Sys::print_positions(){
    for(i_ = 0; i_ < p_->planets; i_++){
        std::cout << p_->planet[i_].get_name() << '\t' << "(" << p_->planet[i_].get_xx() << ", " << p_->planet[i_].get_xy() << ")" << std::endl;
    }
}

inline void Planet_Sys::print_energy(){
    std::cout << days_ << '\t' << E_ << std::endl;
}

inline void Planet_Sys::print_position_file(std::ofstream *output){
    for(i_ = 1; i_ < p_->planets; i_++){
        output[i_] << days_ << '\t' << p_->planet[i_].get_xx() << '\t' << p_->planet[i_].get_xy() << std::endl;
    }
}

inline void Planet_Sys::print_pos_vel_file(std::ofstream *output){
    for(i_ = 1; i_ < p_->planets; i_++){
        output[i_] << days_ << '\t' << p_->planet[i_].get_xx() << '\t' << p_->planet[i_].get_xy()  << '\t' << p_->planet[i_].get_vx()  << '\t' << p_->planet[i_].get_vy() << std::endl;
    }
}

inline void Planet_Sys::print_energy_file(std::ofstream *output){
    output[0] << days_ << '\t' << E_ << std::endl;
}