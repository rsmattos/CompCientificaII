void solver_to_file(struct ODE_set &set, double *u){
    int i;

    std::ofstream output(set.outfile.c_str());

    output << "t";
    for(i = 0; i < set.dimension; i++){
        output << ",u[" << i << "]"; 
    }
    output << std::endl;

    if(set.method == "forward_euler"){
        Forward_euler forward(set.dimension);

        forward.initial_values(u);
        forward.set_time(set);

        forward.set_system(set.function, &set.params);

        forward.file_CSV_print_system(output);

        while(forward.time() < forward.time_limit()){
            forward.forward_euler_step();
            forward.file_CSV_print_system(output);
        }
    }

    if(set.method == "backward_euler"){
        Backward_euler backward(set.dimension);

        backward.initial_values(u);
        backward.set_time(set);

        backward.set_system(set.function, &set.params);

        backward.file_CSV_print_system(output);

        while(backward.time() < backward.time_limit()){
            backward.backward_euler_step();
            backward.file_CSV_print_system(output);
        }
    }

    if(set.method == "cn"){
        Crank_Nicolson cn(set.dimension);

        cn.initial_values(u);
        cn.set_time(set);

        cn.set_system(set.function, &set.params);

        cn.file_CSV_print_system(output);

        while(cn.time() < cn.time_limit()){
            cn.cn_step();
            cn.file_CSV_print_system(output);
        }
    }

    if(set.method == "heun"){
        Heun heun(set.dimension);

        heun.initial_values(u);
        heun.set_time(set);

        heun.set_system(set.function, &set.params);

        heun.file_CSV_print_system(output);

        while(heun.time() < heun.time_limit()){
            heun.heun_step();
            heun.file_CSV_print_system(output);
        }
    }

    if(set.method == "rk4"){
        RK4 rk4(set.dimension);

        rk4.initial_values(u);
        rk4.set_time(set);

        rk4.set_system(set.function, &set.params);

        rk4.file_CSV_print_system(output);

        while(rk4.time() < rk4.time_limit()){
            rk4.rk4_step();
            rk4.file_CSV_print_system(output);
        }
    }

    if(set.method == "rk23"){
        RK23 rk23(set.dimension);

        rk23.initial_values(u);
        rk23.set_time(set);

        rk23.set_system(set.function, &set.params);

        rk23.file_CSV_print_system(output);

        while(rk23.time() < rk23.time_limit()){
            rk23.rk23_step();
            rk23.file_CSV_print_system(output);
        }
    }

    output.close();
}