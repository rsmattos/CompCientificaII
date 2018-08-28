// metodo de euler atrasado
void backward_euler(ODE_solver &solver){
    while(solver.t() < solver.t_limit()){
        solver.backward_euler_step();
        solver.print_system();
    }
}