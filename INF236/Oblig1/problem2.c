#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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

    int* rows = (int*)malloc(sizeof(int)*np);
    int* row1 = (int*)malloc(sizeof(int)*np);
    int* count = (int*)malloc(sizeof(int)*np);
    int* pos = (int*)malloc(sizeof(int)*np);
    row1[0] = 0;
    pos[0] = 0;

    int** pict;
    int* ptr;
    int** result;
    int* resptr;
    if(rank == 0) {
        result = (int**)malloc(sizeof(int*)*dim);
        resptr = (int*)malloc(sizeof(int)*dim*dim);
        for(i=0; i<dim; i++) {
            result[i] = resptr + i*dim;
        }
    }

    double xstep = 4.0/dim, ystep = 4.0/dim;
    double xmin = -2.0;
    double ymax = 2.0-row1[rank]*ystep;
    double a,b;

    free(rows);
    free(row1);
    free(count);
    free(pos);
    free(pict);
    free(ptr);
    if(rank == 0) {
        free(result);
        free(respt)r;
    }

    MPI_Finalize;
    return 0;
}
