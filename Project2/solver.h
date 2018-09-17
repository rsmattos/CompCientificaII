void planetary_system_rk4(struct ODE_set set, struct Params *p){
    int i;

    // open solver
    Planet_Sys_RK4 solar(set.dimension);

    // open output files
    std::ofstream output[10];

    std::string filename;

    output[0].open("OUTPUT/rk4/energy.dat");

    for(p->i = 1; p->i < p->planets; p->i++){
        filename = "OUTPUT/rk4/" + p->planet[p->i].get_name() + ".dat";

        output[p->i].open(filename.c_str());

        output[p->i] << "dias" << '\t' << "x" << '\t' << "y" << std::endl;
    }

    // solve system
    solar.set_solver(set, p);

    solar.print_position_file(output);
    solar.calc_energy();
    solar.print_energy_file(output);

    for(i = 0; i < set.final; i+=2){
        solar.system_step();
        solar.print_position_file(output);
        solar.calc_energy();
        solar.print_energy_file(output);
    }

    // close files
    for(p->i = 0; p->i < p->planets; p->i++){
        output[p->i].close(); 
    }
}

void planetary_system_verlet(struct ODE_set set, struct Params *p){
    int i;

    // open solver
    Planet_Sys_Verlet solar(set.dimension);

    // open output files
    std::ofstream output[10];

    std::string filename;

    output[0].open("OUTPUT/verlet/energy.dat");

    for(p->i = 1; p->i < p->planets; p->i++){
        filename = "OUTPUT/verlet/" + p->planet[p->i].get_name() + ".dat";

        output[p->i].open(filename.c_str());

        output[p->i] << "dias" << '\t' << "x" << '\t' << "y" << std::endl;
    }

    // solve system
    solar.set_solver(set, p);

    solar.print_position_file(output);
    solar.calc_energy();
    solar.print_energy_file(output);

    for(i = 0; i < set.final; i+=2){
        solar.system_step();
        solar.print_position_file(output);
        solar.calc_energy();
        solar.print_energy_file(output);
    }

    // close files
    for(p->i = 0; p->i < p->planets; p->i++){
        output[p->i].close(); 
    }
}