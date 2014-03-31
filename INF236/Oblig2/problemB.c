#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {

    int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(argc < 3) {
        printf("Not enough arguments, please input epsilon and n\n");
        MPI_Finalize();
        return 0;
    }

    double epsilon, int n;
    epsilon = atof(argv[1]);
    n = atoi(argv[2]);

    return 0;
}
