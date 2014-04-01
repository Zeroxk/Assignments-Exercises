x#include <stdio.h>
#include <math.h>
#include <mpi.h>

double f(double x,int n) {
    int i,j;
    double res,res2;
    res = 0.0;
    for(i=1;i<=n;i++) {
        res2 = 0.0;
        for(j=1;j<=n;j++) {
            double r1 = sin( ((pow(x,i) + pow(x,j))/2) );
            double r2 = 1 - cos( (pow(x,i) + pow(x,j))/2 );
            res2 += r1 * r2;
        }
        res += res2;
    }
    return -3 + res;
}

void sendToAll(double a, double b, int tag) {
    double arr [2];
    arr[0] = a; arr[1] = b;
    int i;
    for(i=0; i<np; i++) {
        if(i != rank) {
            MPI_Send(arr, 2, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
        }
    }
}

void printSol(double start, double end) {
    printf("Root is in [%f,%f]\n",start,end);
}

int main(int argc,char** argv) {

    int rank,np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(argc < 3) {
        printf("Not enough arguments, need 2, epsilon and n\n");
        MPI_Finalize();
        return 0;
    }

    double epsilon = atof(argv[1]);
    int n = atoi(argv[2]);
    double start = 0.0; double end = 1.0;
    
    //Sequential algorithm starts here
    if(np == 1) {
        
        while(end-start > epsilon) {
            double mid = (start+end)/2;
            double midVal = f(mid,n);

            if(midVal == 0 || (end-start)/2 < epsilon) {
                printSol(start,end);
                MPI_Finalze();
                return 0;
            }

            double a = f(startn);
            double b = f(end,n);

            if(a == 0 || b == 0) {
                if(b <= a) {
                    start = end;
                }else {
                    end = start;
                }
                printSol(start,end);
                MPI_Finalize();
                return 0;
            }

            if(midVal*a<0) {
                end = mid;
            }else {
                start = mid;
            }
        }

        printSol(start, end);
        MPI_Finalize();
        return 0;
    }

    //Parallell algorithm starts here
    while(end-start > epsilon) {
        double width = (end-start)/np;
        start = start +(rank*width);
        end = start + ((rank+1)/width);

        double a = f(end,n);
        double b = f(start,n);

        if( ((a < 0 && b > 0) || (a > 0 && b < 0)) && (end-start) <= eps {
            printSol(start, end);
            //Send message to processes to terminate
            
            MPI_Finalize();
            return 0;
        }else if(a == 0 || b == 0) {
            if(a >= b){
                start = end;
            }else {
                end = start;
            }
            SendAll(s
        }else if(a < 0 && b < 0) {
            //Send messages
        }else{
            double tmp[2];
            MPI_Status status;
            MPI_Recv(&tmp, 2, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            //Tag = 2 means we have found the root and should terminate
            if(status.MPI_TAG == 2) {
                MPI_Finalize();
                return 0;
            }
            start = tmp[0];
            end = tmp[1];
        }
    }

    MPI_Finalize();
    return 0;
}
