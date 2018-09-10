void planetary_system(struct ODE_set set, struct Params *p){
    int i;

    // set up solver
    ODE_solver solver(2*set.dimension);
    solver.set_time(set);
    solver.set_system(set.function, p);
    solver.set_kutta();

    double *u = new double[2*set.dimension];

    // calculate new positions and velocities for each planet
    // transform position and velocity in variable vector
    for(p->i = 1; p->i < p->planets; p->i++){
        u[0] = p->planet[p->i].get_xx();
        u[1] = p->planet[p->i].get_xy();
        u[2] = p->planet[p->i].get_vx();
        u[3] = p->planet[p->i].get_vy();

        solver.initial_values(u);
        solver.RK4_step();
        solver.get_variables(u);

        p->planet[p->i].new_position(u[0], u[1]);
        p->planet[p->i].new_velocity(u[2], u[3]);
    }

    std::cout << "primeiro passo" << std::endl;

    for(i = 0; i < p->planets; i++){
        p->planet[i].update_positions();
        p->planet[i].update_velocities();
    
        std::cout << p->planet[i].get_name() << " (" << p->planet[i].get_xx() << ", " << p->planet[i].get_xy() << ")" << std::endl;
    }

    // calculate new positions and velocities for each planet
    // transform position and velocity in variable vector
    for(p->i = 1; p->i < p->planets; p->i++){
        u[0] = p->planet[p->i].get_xx();
        u[1] = p->planet[p->i].get_xy();
        u[2] = p->planet[p->i].get_vx();
        u[3] = p->planet[p->i].get_vy();

        solver.initial_values(u);
        solver.RK4_step();
        solver.get_variables(u);

        p->planet[p->i].new_position(u[0], u[1]);
        p->planet[p->i].new_velocity(u[2], u[3]);
    }

    std::cout << "segundo passo" << std::endl;
    
    for(i = 0; i < p->planets; i++){
        p->planet[i].update_positions();
        p->planet[i].update_velocities();
    
        std::cout << p->planet[i].get_name() << " (" << p->planet[i].get_xx() << ", " << p->planet[i].get_xy() << ")" << std::endl;
    }

    // update positions and velocities
    delete[] u;

}