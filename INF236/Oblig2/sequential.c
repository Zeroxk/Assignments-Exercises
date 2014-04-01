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

int main(int argc, char** argv) {
	int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

	double epsilon;
	int n;
    if(argc < 3) {
        printf("Using default values for epsilon and n\n");
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
        
    while(end-start > epsilon) {
        double mid = (start+end)/2;
        double midVal = f(mid,n);

        if(midVal>=0) {
            end = mid;
        }else {
            start = mid;
        }
    }

    printf("Root is in [%1.50f,%1.50f]\n",start,end);
    double stopTime = MPI_Wtime();
    printf("This took %.5f seconds\n", stopTime-startTime);
    MPI_Finalize();
    return 0;
}

