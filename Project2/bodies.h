class Bodies{
    private:
        // potition
        double x_[3];
        double next_x_[3];
        // velocity
        double v_[3];
        double next_v_[3];

        // mass
        double m_;
        // name
        std::string name_;

    public:
        // constructor
        Bodies(){};

        // setting things
        void set_position(double *x);
        void set_position(double x, double y, double z);
        void set_velocity(double *v);
        void set_velocity(double vx, double vy, double vz);
        void set_mass(double mass);
        void set_name(std::string name);
        void new_position(double x, double y, double z);
        void new_velocity(double vx, double vy, double vz);

        // methods
        void update_positions();
        void update_velocities();

        // get values
        double get_xx(){return x_[0];}
        double get_xy(){return x_[1];}
        double get_xz(){return x_[2];}
        double get_vx(){return v_[0];}
        double get_vy(){return v_[1];}
        double get_vz(){return v_[2];}
        double get_mass(){return m_;}
        std::string get_name(){return name_;}
};

inline void Bodies::set_position(double *x){
    x_[0] = x[0];
    x_[1] = x[1];
    x_[2] = x[2];
}
inline void Bodies::set_position(double x, double y, double z){
    x_[0] = x;
    x_[1] = y;
    x_[2] = z;
}

inline void Bodies::set_velocity(double *v){
    v_[0] = v[0];
    v_[1] = v[1];
    v_[2] = v[2];
}
inline void Bodies::set_velocity(double vx, double vy, double vz){
    v_[0] = vx;
    v_[1] = vy;
    v_[2] = vz;
}

inline void Bodies::set_mass(double mass){
    m_ = mass;
}

inline void Bodies::set_name(std::string name){
    name_ = name;
}

inline void Bodies::new_position(double x, double y, double z){
    next_x_[0] = x;
    next_x_[1] = y;
    next_x_[2] = z;
}

inline void Bodies::new_velocity(double vx, double vy, double vz){
    next_v_[0] = vx;
    next_v_[1] = vy;
    next_v_[2] = vz;
}

inline void Bodies::update_positions(){
    x_[0] = next_x_[0];
    x_[1] = next_x_[1];
    x_[2] = next_x_[2];
}

inline void Bodies::update_velocities(){
    v_[0] = next_v_[0];
    v_[1] = next_v_[1];
    v_[2] = next_v_[2];
}