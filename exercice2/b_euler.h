class Backward_euler: public ODE_solver{
    protected:
        double *old_u_;
        double *new_u_;

    public:
        // constructor
        Backward_euler(int N);

        // methods
        void backward_euler_step();

        // destructor
        ~Backward_euler(){
            delete[] old_u_;
            delete[] new_u_;
        }
};

inline Backward_euler::Backward_euler(int N):ODE_solver(N){
    old_u_ = new double[N];
    new_u_ = new double[N];
}

double distance(double *u, double *v, int dim){
    int i;
    double sum = 0;

    for(i = 0; i < dim; i++){
        sum += (u[i] - v[i])*(u[i] - v[i]);
    }

    return sum;
}

inline void Backward_euler::backward_euler_step(){
    time_ = time_ + step_size_;

    loop_counter_ = 0;

    for(i_ = 0; i_ < dim_; i_++){
        old_u_[i_] = u_[i_];
    }

    do{
        for(i_ = 0; i_ < dim_; i_++){
            new_u_[i_] = u_[i_];
        }

        system_(u_, der_u_, time_, params_);

        for(i_ = 0; i_ < dim_; i_++){
            u_[i_] = old_u_[i_] + step_size_*der_u_[i_];
        }

        loop_counter_++;

        if(loop_counter_ > 20){break;}

    }while(distance(u_, new_u_, dim_) > .001*step_size_);
        
    step_counter_++;
}