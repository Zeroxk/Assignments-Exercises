#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

int isPrime(int n) {
    if(n == 0 || n == 1 || n == 2) return 0;
    int i;
    for(i=2; i<=(int)sqrt((double)n); i++){
        if(n%i == 0) return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {
    int rank,np,n,val,res;
    n = 20; res,val = 0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(rank == 0) {
        int i;
        for(i=1; i<np; i++) {
            val += (n/(np-1));
            printf("Sending value %d\n",val);
            MPI_Send(&val,1,MPI_INT,i,1,MPI_COMM_WORLD);
        }
    }else {
        MPI_Status status;
        MPI_Recv(&val,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        printf("Process %d received value %d\n",rank,val);

        int i;
        int a,b;
        for(i=(n-val); i<val; i++) {
            if(isPrime(i) && isPrime(i+2)) {
                printf("(%d,%d)\n",i,i+2);
                res++;
            }
        }
        printf("%d consecutive prime pairs from process %d\n",res-1,rank);

    }

    MPI_Finalize();

    return 0;
}
