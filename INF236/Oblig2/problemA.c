#include <stdio.h>
#include <math.h>
#include <mpi.h>

double f(double x,int n) {
    int i,j;
    double res;
    res = 0.0;
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            double r1 = sin( ((pow(x,i) + pow(x,j))/2) );
            double r2 = 1 - cos( (pow(x,i) + pow(x,j))/2 );
            res += r1 * r2;
        }
    }
    return -3 + res;
}

void printSol(double start, double end) {
    printf("Root is in [%1.50f,%1.50f]\n",start,end);
}

int main(int argc,char** argv) {

    int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    double epsilon; int n;
    if(argc < 3) {
        printf("Not enough arguments, using default values for epsilon and n\n");
        epsilon = pow(2,-30);
        n = 100;
    }else {
        double epsilon = atof(argv[1]);
        int n = atoi(argv[2]);
    }

    double startTime;
    if(rank == 0) {
        startTime = MPI_Wtime();
    }
    double start = 0.0; double end = 1.0;
    
    while(end-start > epsilon) {
        double width = (end-start);
        start = start +(rank*width)/np;
        end = start + width/np;

        double a = f(start,n);
        double b = f(end,n);
        
        if( (a > 0) != (b > 0) ) {
            int i;
            for(i=0; i<np; i++) {
                if(i != rank) {
                    double tmp[2];
                    tmp[0] = start;
                    tmp[1] = end;
                    MPI_Send(tmp, 2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
                }
            }
        }else {
            double tmp[2];
            MPI_Status status;
            MPI_Recv(tmp, 2, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            start = tmp[0];
            end = tmp[1];
        }
         
    }     

    if(rank == 0) {
        double stopTime = MPI_Wtime();
        printSol(start,end);
        printf("This took %.5f seconds\n", stopTime-startTime);
    }
    MPI_Finalize();
    return 0;
}
