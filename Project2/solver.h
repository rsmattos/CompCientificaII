void planetary_system(struct ODE_set set, struct Params *p){
    Planet_Sys_RK4 solar(2);

    solar.set_solver(set, p);

    std::ofstream output[10];

    std::string filename;

    output[0].open("energy_rk4.dat");

    for(p->i = 1; p->i < p->planets; p->i++){
        filename = p->planet[p->i].get_name() + ".dat";

        output[p->i].open(filename.c_str());

        output[p->i] << "x" << '\t' << "y" << std::endl;
    }

    solar.system_step();
    solar.system_step();
    solar.print_position_file(output);
    solar.calc_energy();
    solar.print_energy_file(output);

    for(p->i = 0; p->i < p->planets; p->i++){
        output[p->i].close(); 
    }
}