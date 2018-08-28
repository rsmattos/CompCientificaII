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

        ODE_solver(int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            step_counter_ = 0;
        }

        ODE_solver(double t, double t_limit, double step, int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            time_ = t;
            t_limit_ = t_limit - step;
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
            t_limit_ = t_limit - step;
            step_size_ = step;
            step_counter_ = 0;
        }

        // solvers
        void forward_euler_step();

        void backward_euler_step();

        // return values
        double h(){return step_size_;}

        double t(){return time_;}

        double t_limit(){return t_limit_;}

        int dim(){return dim_;}

        int step_counter(){return step_counter_;}

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

inline void ODE_solver::forward_euler_step(){
    int i;

    system_(u_, der_u_, time_);

    for(i = 0; i < dim_; i++){
        u_[i] += step_size_*der_u_[i];
    }

    time_ = time_ + step_size_;
    step_counter_++;
}

double distance(double *u, double *v, int dim){
    int i;
    double sum = 0;

    for(i = 0; i < dim; i++){
        sum += (u[i] - v[i])*(u[i] - v[i]);
    }

    return sum;
}

inline void ODE_solver::backward_euler_step(){
    int i;
    double * old_u_ = new double[dim_];
    double * new_u_ = new double[dim_];

    time_ = time_ + step_size_;

    for(i = 0; i < dim_; i++){
        old_u_[i] = u_[i];
    }

    do{
        for(i = 0; i < dim_; i++){
            new_u_[i] = u_[i];
        }

        system_(u_, der_u_, time_);

        for(i = 0; i < dim_; i++){
            u_[i] = old_u_[i] + step_size_*der_u_[i];
        }

    }while(distance(u_, new_u_, dim_) > .001*step_size_);
        
    step_counter_++;

    delete[] old_u_;
    delete[] new_u_;
}

inline void ODE_solver::print_system(){
    int i; 

    std::cout << "t = " << time_;
    for(i = 0; i < dim_; i++){
        std::cout << " u[" << i << "] = " << u_[i] << " du[" << i << "] = " << der_u_[i]; 
    }
    std::cout << std::endl;
}

inline void ODE_solver::print_in_time(double t){
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

inline void ODE_solver::file_CSV_print_system(std::ofstream &output){
    int i; 

    output << time_;
    for(i = 0; i < dim_; i++){
        output << "," << u_[i] << "," << der_u_[i]; 
    }
    output << std::endl;
}

inline void ODE_solver::file_CSV_print_in_time(double t,std::ofstream &output){
    int i;

    if( remainder(time_, t) < 1.e-5){
        file_CSV_print_system(output);
    }
}

inline void ODE_solver::file_CSV_print_in_step(int step,std::ofstream &output){
    if( (step_counter_ % step) == 0){
        file_CSV_print_system(output);
    }
}