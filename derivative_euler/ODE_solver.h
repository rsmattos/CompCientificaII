// class for the system of equaitons
class ODE_solver{
    private:
        // time params
        double time_;
        double t_limit_;
        double step_size_;
        int step_counter_;

        // function pointer to the functions being avaliated
        typedef void (*fptr)(double *u, double *du, double t);

        // variables
        double * u_;
        double * der_u_;
        int dim_;
        fptr system_;

    public:
        // constructor
        ODE_solver(){
            u_ = new double;
            der_u_ = new double;

            step_counter_ = 0;
        }

        ODE_solver(double t, double t_limit, double step, int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            time_ = t;
            t_limit_ = t_limit;
            step_size_ = step;
            step_counter_ = 0;
        }
        
        // set parameters
        void initial_values(double *u, double *du){
            u_ = u;
            der_u_ = du;
        }

        void set_system(fptr func){
            system_ = func;
        }

        void set_time(double t = 0.0, double t_limit = 10., double step = 0.01){
            time_ = t;
            t_limit_ = t_limit;
            step_size_ = step;
            step_counter_ = 0;
        }

        void forward_euler_step();

        // return values
        double h(){return step_size_;}

        double t(){return time_;}

        double t_limit(){return t_limit_;}

        int dim(){return dim_;}

        int step_counter(){return step_counter_;}

        void print_system();

        void print_system(double);

        void print_in_step(int);

        // destructor
        ~ODE_solver(){
            delete[] u_;
            delete[] der_u_;
        }
};

inline void ODE_solver::forward_euler_step(){
    int i;

    system_(u_, der_u_, time_);

    for(i = 0; i < dim_; i++){
        u_[i] += step_size_*der_u_[i];
    }

    time_ = time_ + step_size_;
    step_counter_++;
}

inline void ODE_solver::print_system(){
    int i;

    std::cout << "t = " << time_;
    for(i = 0; i < dim_; i++){
        std::cout << " u[" << i << "] = " << u_[i] << " du[" << i << "] = " << der_u_[i]; 
    }
    std::cout << std::endl;
}

inline void ODE_solver::print_system(double t){
    int i;

    if( remainder(time_, t) < 1.e-5){
        print_system();
    }
}

inline void ODE_solver::print_in_step(int step){
    if( (step_counter_ % step) == 0){
        print_system();
    }
}