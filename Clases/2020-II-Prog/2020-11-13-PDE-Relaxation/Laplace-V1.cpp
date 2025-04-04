#include <iostream>
#include <vector>

const double DELTA = 0.1;
const double XMIN = 0.0;
const double XMAX = 1.0;
const double YMIN = 0.0;
const double YMAX = 1.2;
const int NX = (XMAX-XMIN)/DELTA;
const int NY = (YMAX-YMIN)/DELTA;
const int NSTEPS = 1;

typedef std::vector<double> data_t;

void initial_conditions(data_t & data, int nx, int ny);
void boundary_conditions(data_t & data, int nx, int ny);
void evolve(data_t & data, int nx, int ny, int nsteps);
void relaxation_step(data_t & data, int nx, int ny);
void print_screen(const data_t & data, int nx, int ny);
void print_gnuplot(const data_t & data, int nx, int ny);


int main(int argc, char **argv)
{
    // declare data structures
    data_t potential(NX*NY);

    // set initial and boundary conditions
    initial_conditions(potential, NX, NY);
    boundary_conditions(potential, NX, NY);

    // evolve and print
    evolve(potential, NX, NY, NSTEPS);

    return 0;
}

void initial_conditions(data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 1.0;
        }
    }
}
void boundary_conditions(data_t & data, int nx, int ny)
{
    int ix, iy;
    // first row
    ix = 0;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 100.0;
    }
    // last row
    ix = nx-1;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 0.0;
    }
    // first row
    iy = 0;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    // last row
    iy = ny-1;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
}

void evolve(data_t & data, int nx, int ny, int nsteps)
{
    for(int istep = 0; istep < nsteps; ++istep) {
        relaxation_step(data, nx, ny);
        //print_screen(data, nx, ny);
        print_gnuplot(data, nx, ny);
    }
}
void relaxation_step(data_t & data, int nx, int ny)
{
    // recorrer toda la matriz y aplicar el algoritmo,
    // teniendo cuidado con no modificar las condiciones de
    // frontera
    for(int ix = 1; ix < nx-1; ++ix) {
        for(int iy = 1; iy < ny-1; ++iy) {
            // check that this cell is NOT a boundary condition or a border
            // update the cell
            data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;;
        }
    }

}
void print_screen(const data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            std::cout << data[ix*ny + iy] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_gnuplot(const data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        double x = XMIN + ix*DELTA;
        for(int iy = 0; iy < ny; ++iy) {
            double y = YMIN + iy*DELTA;
            std::cout << x << "  " << y << "  " << data[ix*ny + iy] << "\n";
        }
        std::cout << "\n";
    }
}
