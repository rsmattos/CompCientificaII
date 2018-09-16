void planetary_system(struct ODE_set set, struct Params *p){
    Planet_Sys_RK4 solar(2);

    solar.set_solver(set, p);

    solar.system_step();
    solar.system_step();
    solar.print_positions();
    solar.calc_energy();
    solar.print_energy();
}