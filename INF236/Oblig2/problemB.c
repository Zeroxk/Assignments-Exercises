#include <mpi.h>
#include <stdio.h>
#include <math.h>

double f(double x, int n) {

    int i,j;
    double res = 0.0;
    for(i=1;i<=n;i++) {
        for(j=1; j<=n; j++) {
            double r1= sin( ((pow(x,i) + (pow(x,j)))/2) );
            double r2 = 1 - cos( (pow(x,i) + pow(x,j))/2);
            res += r1 * r2;
        }
    }
    return -3 + res;

}

void printSol(double start, double end) {
    printf("Root is in [%1.50f,%1.50f]\n", start, end);
}

int main(int argc, char** argv) {

    int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    double epsilon; int n;
    if(argc < 3) {
        printf("Using default values for epsilon=2^-31 and n=100\n");
        epsilon = pow(2,-30);
        n = 100;
    }else {
        epsilon = atof(argv[1]);
        n = atoi(argv[2]);
    }

    double startTime;
    if(rank == 0) {
        startTime = MPI_Wtime();
    }
    double start = 0.0; double end = 1.0;
    
    double vals [np];
    while( (end-start) > epsilon) {
        double width = (end-start);
        double point = start + width * (rank+1.0)/(np+1);
        double pointVal = f(point,n);
        MPI_Allgather(&pointVal, 1, MPI_DOUBLE, vals, 1, MPI_DOUBLE, MPI_COMM_WORLD);

        //printf("Everything is gathered\n");
        /*
        double tmp = end -  (1.0)/(np+1) * width;
        double tmp2 = end;
        int i;
        for(i=0; i<np; i++) {
            if(vals[i] >= 0) {
                double tmp3 = start + (i+1.0)/(np+1) * width;
                tmp = tmp3; tmp2 = tmp3;
                break;
            }
        }
        start = tmp;
        end = tmp2;
        */

        
        int i;
        for(i=0; i<np; i++) {
            if(vals[i] > 0) {
                //printf("Found new interval\n");
                break;
            }
        }

        start = start + width*i/(np+1);
        end = start + width/(np+1);
        
    }

    if(rank == 0) {
        double stopTime = MPI_Wtime();
        printSol(start,end);
        printf("This took %.5f seconds\n", stopTime-startTime);
    }

    MPI_Finalize();
    return 0;
}
