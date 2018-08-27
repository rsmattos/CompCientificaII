// class for the system of equaitons
class ODE_solver{
    private:
        // time params
        double time_;
        double t_limit_;
        double step_size_;

        // function pointer to the functions being avaliated
        typedef void (*fptr)(double *u, double *du, double t);

        // variables
        double * u_;
        double * der_u_;
        int dim_;
        fptr system_;
    public:
        // constructor
        ODE_solver(double t = 0.0, double t_limit = 10., double step = 0.01, int N = 2){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            time_ = t;
            t_limit_ = t_limit;
            step_size_ = step;
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
        }

        void forward_euler_step();

        // return values
        double h(){return step_size_;}

        double t(){return time_;}

        int dim(){return dim_;}

        void print_system();

        // destructor
        ~ODE_solver(){
            delete[] u_;
            delete[] der_u_;
        }
};

inline void ODE_solver::forward_euler_step(){
    int i;

    system_;

    for(i = 0; i < dim_; i++){
        u_[i] += step_size_*der_u_[i];
    }

    time_ = time_ + step_size_;
}

inline void ODE_solver::print_system(){
    int i;

    std::cout << "t = " << time_;
    for(i = 0; i < dim_; i++){
        std::cout << " u[" << i << "] = " << u_[i] << " du[" << i << "] = " << der_u_[i]; 
    }
    std::cout << std:: endl;
}
