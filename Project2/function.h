void planetary3D(double *u, double *du, double t, struct Params *p){
    int i;
    
    du[0] = u[3];
    du[1] = u[4];
    du[2] = u[5];

    du[3] = 0.;
    du[4] = 0.;
    du[5] = 0.;

    for(i = 0; i < p->planets ; i++){
        if(i == p->i){
            continue;
        }
        du[3] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) +
                (p->planet[i].get_xz() - u[2])*(p->planet[i].get_xz() - u[2]), 1.5);

        du[4] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) +
                (p->planet[i].get_xz() - u[2])*(p->planet[i].get_xz() - u[2]), 1.5);

        du[5] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[2])/
           pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) +
                (p->planet[i].get_xz() - u[2])*(p->planet[i].get_xz() - u[2]), 1.5);
    }

    du[3] = p->G*du[3];
    du[4] = p->G*du[4];
    du[5] = p->G*du[5];
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
