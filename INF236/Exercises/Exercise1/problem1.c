#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank,np,n;
    n = 4;
    double numbers[n];
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0) {
        int i;
        printf("Creating number array\n");
        for(i=0; i<n; i++){
            numbers[i] = rand()%1;
        }
        printf("i \t val\n");
        for(i=0; i<n; i++) {
            printf("%d \t %d\n",i,numbers[i]);
        }

        for(i=1; i<np; i++) {
            MPI_Send(&numbers,np,MPI_INT,i,1,MPI_COMM_WORLD);
        }
        
    }else {
        MPI_Status status;
        MPI_Recv(&numbers,n, MPI_INT,0,1,MPI_COMM_WORLD,&status);
        int i,sum=0;
        for(i=0; i<n; i++) {
            sum += pow(numbers[i],rank);
        }
        printf("Sum from process %d is %d\n",rank,sum);
    }

    MPI_Finalize();
    return 0;
} 
