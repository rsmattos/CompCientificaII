#include "header.h"

int main(){
    // declaracao da classe de ODE
    ODE_solver solver1(0., 10., .1, 2);

    double u[] = {1., 1.};
    double du[] = {1., 1.};

    solver1.initial_values(u, du);

    solver1.set_system(exponential2D);

    solver1.print_system();

    solver1.forward_euler_step();

    solver1.print_system();

    solver1.forward_euler_step();

    solver1.print_system();

    return 0;
}
