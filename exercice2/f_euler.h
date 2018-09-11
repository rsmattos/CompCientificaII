class Forward_euler: public ODE_solver{
    public:
        // constructor
        Forward_euler(int N);

        //methods
        void forward_euler_step();

        // destructor
        ~Forward_euler(){}
};

inline Forward_euler::Forward_euler(int N):ODE_solver(N){}

inline void Forward_euler::forward_euler_step(){
    system_(u_, der_u_, time_, params_);

    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] += step_size_*der_u_[i_];
    }

    time_ = time_ + step_size_;
    step_counter_++;
}
