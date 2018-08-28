// class for the system of equaitons
class ODE_solver{
    private:
        // time params
        double time_;
        double t_limit_;
        double step_size_;
        int step_counter_;
        int method[3];
        int i_;

        // function pointer to the functions being avaliated
        typedef void (*fptr)(double *u, double *du, double t);

        // variables
        double * u_;
        double * der_u_;
        double * old_u_, * new_u_;       // forward
        double * cn_der_u_;               // cn
        int dim_;
        fptr system_;

    public:
        // constructor
        ODE_solver(int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            step_counter_ = 0;

            method[0] = 0;                // Backward
            method[1] = 0;                // CN
            method[2] = 0;                // Huen
        }

        ODE_solver(double t, double t_limit, double step, int N){
            dim_ = N;
            u_ = new double[N];
            der_u_ = new double[N];

            step_counter_ = 0;

            method[0] = 0;                // Backward
            method[1] = 0;                // CN
            method[2] = 0;                // Huen

            time_ = t;
            t_limit_ = t_limit - step;
            step_size_ = step;
        }

        void set_backward(){
            old_u_ = new double[dim_];
            new_u_ = new double[dim_];

            method[0] = 1;
        }

        void set_cn(){
            set_backward();

            cn_der_u_ = new double[dim_];

            method[1] = 1;
        }

        void set_huen(){
            method[2] = 1;
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

        void set_time(struct ODE_set &set){
            time_ = set.initial;
            t_limit_ = set.final - set.step;
            step_size_ = set.step;
            step_counter_ = 0;
        }

        // solvers
        void forward_euler_step();

        void backward_euler_step();

        void cn_step();

        void huen_step();

        // return values
        double h(){return step_size_;}

        double t(){return time_;}

        double t_limit(){return t_limit_;}

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

            if(method[0] == 1){
                delete[] old_u_;
                delete[] new_u_;
            }

            if(method[1] == 1){
                delete[] cn_der_u_;
            }

            if(method[2] == 1){
                
            }
        }
};

inline void ODE_solver::forward_euler_step(){
    system_(u_, der_u_, time_);

    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] += step_size_*der_u_[i_];
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
    time_ = time_ + step_size_;

    for(i_ = 0; i_ < dim_; i_++){
        old_u_[i_] = u_[i_];
    }

    do{
        for(i_ = 0; i_ < dim_; i_++){
            new_u_[i_] = u_[i_];
        }

        system_(u_, der_u_, time_);

        for(i_ = 0; i_ < dim_; i_++){
            u_[i_] = old_u_[i_] + step_size_*der_u_[i_];
        }

    }while(distance(u_, new_u_, dim_) > .001*step_size_);
        
    step_counter_++;
}

inline void ODE_solver::cn_step(){
    // calculate fn
    system_(u_, cn_der_u_, time_);

    // calculate fn+i, already atualizes the steo counter and time
    backward_euler_step();

    // calculate the cn step
    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = old_u_[i_] + step_size_*(cn_der_u_[i_] + der_u_[i_]) / 2.;
    }
}

inline void ODE_solver::huen_step(){
    
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