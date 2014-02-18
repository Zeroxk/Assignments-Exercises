#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int isPrime(int n) {
    int i;
    for(i=2; i<sqrt(n); i++){
        if(n%i == 0) return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {
    int rank,np,n,val,res;
    n = 20; res = 0;
    MPI_INIT(&argc,&argv)
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank) {
        int i;
        for(i=1; i<np; i++){
            MPI_Send(&val,np,MPI_INT,i,1,MPI_COMM_WORLD);
        }
    }else {
        MPI Status status;
        MPI_Recv(&val,np,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        int i;
        int a,b;
        for(i=val-(n/np); i<=val-2; i+=2) {
            if(isPrime(i) && isPrime(i+2)) {
                res++;
            }
        }
    }
}
