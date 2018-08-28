// metodo de euler avancado
void forward_euler(ODE_solver &solver){
    while(solver.t() < solver.t_limit()){
        solver.forward_euler_step();
        solver.print_system();
    }
}

// metodo de euler avancado
void forward_euler(ODE_solver &solver, std::ofstream &output){
    int i;

    output << "t";
    for(i = 0; i < solver.dim(); i++){
        output << ",u[" << i << "],du[" << i << "]"; 
    }
    output << std::endl;

    while(solver.t() < solver.t_limit()){
        solver.forward_euler_step();
        solver.file_CSV_print_system(output);
    }
}