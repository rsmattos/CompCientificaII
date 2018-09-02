void exponential1D(double *u, double *du, double t){
    du[0] = u[0];
}

void exponential2D(double *u, double *du, double t){
    du[0] = u[0];
    du[1] = u[1];
}

void exemplo_1(double *u, double *du, double t){
    du[0] = u[0];
}

void exemplo_2(double *u, double *du, double t){
    du[0] = -5*u[0];
}

void exemplo_3(double *u, double *du, double t){
    du[0] = (u[0] - t)/(u[0] + t);
}

void VanDerPol(double *u, double *du, double t){
    du[0] = u[1];
    du[1] = -.1*u[1]*(u[0]*u[0] - 1.) - u[0];
}

void Lorenz(double *u, double *du, double t){
    du[0] = 10.*(u[1] - u[0]);
    du[1] = u[0]*(27 - u[2]) - u[1];
    du[2] = u[0]*u[1] - 8.*u[2]/3.;
}