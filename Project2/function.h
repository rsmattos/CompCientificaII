void planetary2D(double *u, double *du, double t, struct Params *p){
    int i;

    double distance_sqr;
    
    du[0] = u[2];
    du[1] = u[3];

    du[2] = 0.;
    du[3] = 0.;

    // std::cout << "posicao do planeta atual" << std::endl;
    // std::cout << u[0] << std::endl;
    // std::cout << u[1] << std::endl;

    for(i = 0; i < p->planets ; i++){
        if(i == p->i){
            continue;
        }

        distance_sqr = (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                       (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]);

        du[2] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
                 (distance_sqr*sqrt(distance_sqr));

        du[3] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
                 (distance_sqr*sqrt(distance_sqr));

        // du[2] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
        //    pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
        //         (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);

        // std::cout << "comparando com " << p->planet[i].get_name() << std::endl;
        // std::cout << p->planet[i].get_xx() << std::endl;
        // std::cout << p->planet[i].get_xy() << std::endl;

        // std::cout << "diferencas de posicao" << std::endl;
        // std::cout << p->planet[i].get_xx() - u[0] << std::endl;
        // std::cout << p->planet[i].get_xy() - u[1] << std::endl;

        // du[3] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
        //    pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
        //         (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);
    }

    du[2] = p->G*du[2];
    du[3] = p->G*du[3];

    // std::cout << "velocidades" << std::endl;
    // std::cout << du[0] << std::endl;
    // std::cout << du[1] << std::endl;

    // std::cout << "aceleracoes" << std::endl;
    // std::cout << du[2] << std::endl;
    // std::cout << du[3] << std::endl;

}

void planetary2D_verlet(double *u, double *du, double t, struct Params *p){
    double distance_sqr;
    int i;

    du[0] = 0.;
    du[1] = 0.;

    for(i = 0; i < p->planets ; i++){
        if(i == p->i){
            continue;
        }

        distance_sqr = (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
                       (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]);

        du[0] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
                 (distance_sqr*sqrt(distance_sqr));

        du[1] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
                 (distance_sqr*sqrt(distance_sqr));

        // du[0] += p->planet[i].get_mass()*(p->planet[i].get_xx() - u[0])/
        //    pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
        //         (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);

        // du[1] += p->planet[i].get_mass()*(p->planet[i].get_xy() - u[1])/
        //    pow( (p->planet[i].get_xx() - u[0])*(p->planet[i].get_xx() - u[0]) +
        //         (p->planet[i].get_xy() - u[1])*(p->planet[i].get_xy() - u[1]) , 1.5);
    }

    du[0] = p->G*du[0];
    du[1] = p->G*du[1];
}
