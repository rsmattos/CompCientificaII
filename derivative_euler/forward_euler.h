// metodo de euler avancado
void forward_euler(ODE_solver &solver){
    while(solver.t() < solver.t_limit()){
        solver.forward_euler_step();
        solver.print_system();
    }
}