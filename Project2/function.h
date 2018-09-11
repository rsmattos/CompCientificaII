void planetary2D(double *u, double *du, double t, struct Params *p){
    int i;
    
    du[0] = u[2];
    du[1] = u[3];

    du[2] = 0.;
    du[3] = 0.;

    for(i = 0; i < p->planets ; i++){
        if(i == p->i){
            continue;
        }
        du[2] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);

        du[3] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);
    }

    du[2] = p->G*du[2];
    du[3] = p->G*du[3];
}

void planetary2D_verlet(double *u, double *du, double t, struct Params *p){
    int i;

    du[0] = 0.;
    du[1] = 0.;

    for(i = 0; i < p->planets ; i++){
        if(i == p->i){
            continue;
        }
        du[0] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);

        du[1] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);
    }

    du[0] = p->G*du[0];
    du[1] = p->G*du[1];
}
