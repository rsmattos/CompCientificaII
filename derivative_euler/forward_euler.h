// metodo de euler avancado

struct Parameters{
    double h;
    double t;
    double t_limit;
    int N;
};

struct Variables{
    double u;
    double du;
};

void exponential(Variables *vars, Parameters *params){
    int i;

    for(i = 0; i < params->N; i++){
        vars[i].du = vars[i].u;
    }
}

void step(Variables *vars, Parameters *params, void (*f)(Variables *vars, Parameters *params)){
    int i;

    for(i=0; i<params->N; i++){
        (*f)(vars, params);
    }

    for(i = 0; i < params->N; i++){
        vars[i].u = vars[i].u + params->h*vars[i].du;
    }

    params->t += params->h;
}

void feuler(){
    int i, counter;

    Parameters * params = new Parameters;

    params->h = 0.1;
    params->t = 0.;
    params->t_limit = 7.0;
    params->N = 1;

    Variables * vars = new Variables[params->N];

    std::cout << '\t' << "t";
    for(i = 0; i < params->N; i++){
        std::cout << '\t' << "u" << i;
    }
    for(i = 0; i < params->N; i++){
        std::cout << '\t' << "du" << i;
    }
    std::cout << std::endl;

    for(i = 0; i < params->N; i++){
        vars[i].u = 1.;
        vars[i].du = 1.;
    }

    void (*f)(Variables*, Parameters*);

    f = &exponential;

    counter = 0;

    while(params->t < params->t_limit){
        step(vars, params, (*f));
        std::cout << '\t' << params->t;
        for(i = 0; i < params->N; i++){
            std::cout << '\t' << vars[i].u << i;
        }
        for(i = 0; i < params->N; i++){
            std::cout << '\t' << vars[i].du << i;
        }
        std::cout << std::endl;

        counter++;

        if(counter > 100){
            break;
        }
    }


    delete[] vars;
}