// class for the system of equaitons
class ODE_solver{
    protected:
        // time params
        double time_;
        double t_limit_;
        double step_size_;
        int step_counter_;
        int i_;

        // function pointer to the functions being avaliated
        typedef void (*fptr)(double *u, double *du, double t, struct Params *params);
        struct Params *params_;
        fptr system_;

        // variables
        double * u_;
        double * der_u_;
        int dim_;

    public:
        // constructors
        ODE_solver(int N);

        // set parameters
        void initial_values(double *u);
        void set_system(fptr func, struct Params *params);
        void set_time(double t, double t_limit, double step);
        void set_time(struct ODE_set &set);

        // return values
        double step_size(){return step_size_;}
        double time(){return time_;}
        double time_limit(){return t_limit_;}
        void get_variables(double *u);
        int dim(){return dim_;}
        int step_counter(){return step_counter_;}

        // functions to print variables
        void print_system();
        void print_in_time(double);
        void print_in_step(int);
        void file_CSV_print_system(std::ofstream&);
        void file_CSV_print_in_time(double, std::ofstream&);
        void file_CSV_print_in_step(int, std::ofstream&);

        // destructor
        ~ODE_solver(){
            delete[] u_;
            delete[] der_u_;
        }
};

inline ODE_solver::ODE_solver(int N){
    dim_ = N;
    u_ = new double[N];
    der_u_ = new double[N];

    step_counter_ = 0;
}

inline void ODE_solver::initial_values(double *u){
    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = u[i_];
    }
}

inline void ODE_solver::set_system(fptr func, struct Params *params){
    system_ = func;
    params_ = params;
}

inline void ODE_solver::set_time(double t = 0.0, double t_limit = 10., double step = 0.01){
    time_ = t;
    t_limit_ = t_limit - step;
    step_size_ = step;
    step_counter_ = 0;
}

inline void ODE_solver::set_time(struct ODE_set &set){
    time_ = set.initial;
    t_limit_ = set.final - set.step;
    step_size_ = set.step;
    step_counter_ = 0;
}

inline void ODE_solver::get_variables(double *u){
    for(i_ = 0; i_ < dim_; i_++){
        u[i_] = u_[i_];
    }
}

inline void ODE_solver::print_system(){
    std::cout << "t = " << time_;
    for(i_ = 0; i_ < dim_; i_++){
        std::cout << " u[" << i_ << "] = " << u_[i_]; 
    }
    std::cout << std::endl;
}

inline void ODE_solver::print_in_time(double t){
    if( remainder(time_, t) < 1.e-5){
        print_system();
    }
}

inline void ODE_solver::print_in_step(int step){
    if( (step_counter_ % step) == 0){
        print_system();
    }
}

inline void ODE_solver::file_CSV_print_system(std::ofstream &output){
    output << time_;
    for(i_ = 0; i_ < dim_; i_++){
        output << "," << u_[i_]; 
    }
    output << std::endl;
}

inline void ODE_solver::file_CSV_print_in_time(double t,std::ofstream &output){
    if( remainder(time_, t) < 1.e-5){
        file_CSV_print_system(output);
    }
}

inline void ODE_solver::file_CSV_print_in_step(int step,std::ofstream &output){
    if( (step_counter_ % step) == 0){
        file_CSV_print_system(output);
    }
}