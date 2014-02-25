  1 #include <stdio.h>
  2 #include <stdlib.h
  3 #include <time.h>
  4 #include <mpi.h>
  5 #include <math.h>
  6
  7 int isPrime(int n) {
  8     if(n == 1) return 0;
  9     int i;
 10     for(i=2; i<=(int)sqrt((double)n); i++){
 11         if(n%i == 0) return 0;
 12     }
 13
 14     return 1;
 15 }
 16
 17 int main(int argc, char* argv[]) {
 18     int rank,np,n,val,res,total;
 19     n = 20; res,total,val= 0;
 20     MPI_Init(&argc,&argv);
 21     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 22     MPI_Comm_size(MPI_COMM_WORLD, &np);
 23
 24     if(rank == 0) {
 25         int i;
 26         for(i=1; i<np; i++) {
 27             val += (n/(np-1));
 28             printf("Sending value %d to process %d\n",val,i);
 29             MPI_Send(&val,1,MPI_INT,i,1,MPI_COMM_WORLD);
 30         }
 31
 32     }else {
 33         MPI_Status status;
 34         MPI_Recv(&val,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
 35         printf("Process %d received value %d\n",rank,val);
 36
 37         int i;
 38         int a,b;
 39         for(i=(val-(n/(np-1))); i<val; i++) {
 40             //printf("i:%d\n",i);
 41             if(i%2 == 0) continue;
 42             if(isPrime(i) && isPrime(i+2)) {
 43                 printf("(%d,%d)\n",i,i+2);
 44                 res++;
 45             }
 46         }
 47         printf("%d consecutive prime pairs from process %d\n",res,rank);
 48
 49     }
 50
 51     printf("\nTotal number of consecutive prime pairs is %d\n",res);
 52
 53     MPI_Finalize();
 54
 55     return 0;
 56 }
~
~
~
~
~
~
~
~
~
~
~
~
~
"problem1.c" 56L, 1313C                                       51,5          All
