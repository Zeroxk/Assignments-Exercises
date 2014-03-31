x#include <stdio.h>
#include <math.h>
#include <mpi.h>

double f(double x,int n) {
    int i,j;
    double res,res2;
    res = 0.0;
    for(i=1;i<=n;i++) {
        res2 = 0.0;
        for(j=1;j<=n;j++) {
            double r1 = sin( (pow(x,i) + pow(x,j)/2) );
            double r2 = 1 - cos( (pow(x,i) + pow(x,j))/2 );
            res2 += r1 * r2;
        }
        res += res2;
    }
    return -3 + res;
}

int main(int argc,char** argv) {

    int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(argc < 3) {
        printf("Not enough arguments, need 2, epsilon and n\n");
        MPI_Finalize();
        return 0;
    }

    double epsilon; int n;
    epsilon = atof(argv[1]);
    n = atoi(argv[2]);

    if(rank == 0) {
    
    }


    return 0;
}
