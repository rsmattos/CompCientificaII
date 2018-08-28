// metodo de euler avancado
void solver_to_screen(struct ODE_set &set, double *u, double *du){
    ODE_solver solver(set.dimension);

    solver.initial_values(u, du);
    solver.set_time(set);

    solver.set_system(set.function);

    if(set.method == "forward"){
        while(solver.t() < solver.t_limit()){
            solver.forward_euler_step();
            solver.print_system();
        }
    }

    if(set.method == "backward"){
        solver.set_backward();

        while(solver.t() < solver.t_limit()){
            solver.backward_euler_step();
            solver.print_system();
        }
    }

    if(set.method == "cn"){
        solver.set_cn();

        while(solver.t() < solver.t_limit()){
            solver.cn_step();
            solver.print_system();
        }
    }

    if(set.method == "huen"){
        solver.set_huen();
        while(solver.t() < solver.t_limit()){
            solver.huen_step();
            solver.print_system();
        }
    }
}

// metodo de euler avancado
// metodo de euler avancado
void solver_to_file(struct ODE_set &set, double *u, double *du){
    int i;

    ODE_solver solver(set.dimension);

    solver.initial_values(u, du);
    solver.set_time(set);

    solver.set_system(set.function);

    std::ofstream output(set.outfile.c_str());

    output << "t";
    for(i = 0; i < solver.dim(); i++){
        output << ",u[" << i << "]"; 
    }
    output << std::endl;

    solver.file_CSV_print_system(output);

    if(set.method == "forward"){
        while(solver.t() < solver.t_limit()){
            solver.forward_euler_step();
            solver.file_CSV_print_system(output);
        }
    }

    if(set.method == "backward"){
        solver.set_backward();

        while(solver.t() < solver.t_limit()){
            solver.backward_euler_step();
            solver.file_CSV_print_system(output);
        }
    }

    if(set.method == "cn"){
        solver.set_cn();

        while(solver.t() < solver.t_limit()){
            solver.cn_step();
            solver.file_CSV_print_system(output);
        }
    }

    if(set.method == "huen"){
        solver.set_huen();

        while(solver.t() < solver.t_limit()){
            solver.huen_step();
            solver.file_CSV_print_system(output);
        }
    }

    output.close();
}