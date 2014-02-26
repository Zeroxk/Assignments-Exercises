#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

int isPrime(unsigned int n) {
    if(n == 1) return 0;
    int i;
    for(i=2; i<=(int)sqrt((double)n); i++){
        if(n%i == 0) return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {
    int rank,np,res;
    if(argc < 2) {
        if(rank == 0) printf("Too few arguments\n");
        MPI_Finalize();
        return 0;
    }

    unsigned int n;
    scanf("%d",&n);
    res = 0; 
    unsigned int val= 0;
    int totalPairs = 0;;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    double startTime = MPI_Wtime();
    if(rank == 0) {
         int i;
         for(i=1; i<np; i++) {
             //val += n/np + (i < (n%np));
             val = (n/(np-1))*i; 
             printf("Sending value %d to process %d\n",val,i);
             MPI_Send(&val,1,MPI_INT,i,1,MPI_COMM_WORLD);
         }
         

    }else {
        MPI_Status status;
        MPI_Recv(&val,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        //printf("Process %d received value %d\n",rank,val);

        int i;
        int start,end;
        start = 0+((n/(np-1))*(rank-1));
        printf("Start is %d\n",start);
        //if(val == n) start = (n/(np-1))*rank;
        for(i=start; i<val; i++) {
            //printf("i:%d\n",i);
            if(i%2 == 0) continue;
            if((i+2)<n && isPrime(i) && isPrime(i+2)) {
               printf("(%d,%d)\n",i,i+2);
               res++;
            }
        }
        printf("%d consecutive prime pairs from process %d\n",res,rank);
    }

    MPI_Reduce(&res,&totalPairs,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    double finishTime = MPI_Wtime();
    double elapsed = finishTime-startTime;
    
    if(rank == 0) {
        int i;
        printf("Total consecutive prime pairs between %d and %d is %d\n",1,n,totalPairs);
        printf("This job took %.9f seconds\n",elapsed);
    }

    MPI_Finalize();

    return 0;
}
