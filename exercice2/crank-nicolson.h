class Crank_Nicolson: public Backward_euler{
    protected:
        double *extra_der_u_;

    public:
        // constructor
        Crank_Nicolson(int N);

        // methods
        void cn_step();

        // destructor
        ~Crank_Nicolson(){
            delete[] extra_der_u_;
        }
};

inline Crank_Nicolson::Crank_Nicolson(int N):Backward_euler(N){
    extra_der_u_ = new double[N];
}

inline void Crank_Nicolson::cn_step(){
    // calculate fn
    system_(u_, extra_der_u_, time_, params_);

    // calculate fn+i, already atualizes the steo counter and time
    backward_euler_step();

    // calculate the cn step
    for(i_ = 0; i_ < dim_; i_++){
        u_[i_] = old_u_[i_] + step_size_*(extra_der_u_[i_] + der_u_[i_]) / 2.;
    }
}
