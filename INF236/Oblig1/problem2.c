#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

int printsol(int dim, int result[dim][dim]) {
  int i,j;
  for(i=0;i<dim;i++) {
      int nstars=0;  // Count occurences of * in the ith row
      for(j=0;j<dim;j++) nstars+=result[i][j];
        if(nstars) {   // Nonblank row
            for(j=0;j<dim;j++) {
                if(result[i][j]) printf("*");
                    else printf(" ");
            }
            printf("\n");
        }
    }
}

int inMandel(double a, double b, int nrec) {
    int i = 0;
    double x = 0.0, y = 0.0;
    double tmp;

    while((i<nrec) && ((x*x + y*y)) < (double)4.0) {
        tmp = x*x - y*y + a;
        y = 2*x*y + b;
        x = tmp;
        i++;
    }

    return i == nrec;
}

int main(int argc,char** argv) {

    MPI_Init(&argc,&argv);
    double startTime;
    int rank,np;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&np);

    if(argc < 3) {
        if(rank == 0) printf("Missing arguments\n");
        MPI_Finalize();
        return 0;
    }
    
    int dim = atoi(argv[1]);
    int nrec = atoi(argv[2]);
    int results[dim][dim];
    if(rank == 0) {
        
        startTime = MPI_Wtime();
        int i,j;
        int tmp = 0;
        int workingOn[np];
        memset(workingOn,-1,np+1);

        for(i=1;i<np;i++) {
            MPI_Send(&tmp,1,MPI_INT,i,1,MPI_COMM_WORLD);
            workingOn[i] = tmp;
            tmp++;
        }
        int lastSent = np-1;
        
        //results = (int**)malloc(sizeof(int*)*dim*dim+1);
        //int results[dim][dim];
        for(i=0;i<dim;i++) {
            //printf("Hei\n");
            for(j=0;j<dim;j++) {
                results[i][j] = 0;
            }
            //printf("Hi on you\n");
        }
        while(lastSent < dim) {
            int rcvRow[dim];
            MPI_Status status;
            MPI_Recv(rcvRow,dim,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);
            for(i=0;i<dim;i++) {
                results[workingOn[status.MPI_SOURCE]][i] = rcvRow[i];
            }

            lastSent++;
            int sendTag = lastSent < dim ? 1:2;
            MPI_Send(&lastSent,1,MPI_INT,status.MPI_SOURCE,sendTag,MPI_COMM_WORLD);
            workingOn[status.MPI_SOURCE] = lastSent;

        }

    }else {

        MPI_Status status;
        int rcvRow;
        MPI_Recv(&rcvRow,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        
        while(status.MPI_TAG == 1) {
            int i;
            int pict[dim];
            memset(pict,0,dim);
            double xstep = 4.0/dim, ystep = 4.0/dim;
            double xmin = -2.0;
            double ymax = 2.0;
            double a,b;
            b = ymax - (rcvRow+0.5)*ystep;
            for(i=0;i<dim;i++) {
                a = xmin + (i+0.5)*xstep;
                pict[i] = inMandel(a,b,nrec);
            }

            MPI_Send(pict,dim,MPI_INT,0,1,MPI_COMM_WORLD);
            MPI_Recv(&rcvRow,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        }
    }

    if(!rank) {
        //printsol(dim,results); 
        double endTime = MPI_Wtime();
        printf("Used %.9f seconds\n",endTime-startTime);
    }

    MPI_Finalize();
    return 0;
}
