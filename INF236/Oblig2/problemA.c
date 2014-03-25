#include <stdio.h>
#include <math.h>
#include <mpi.h>

double f(double x,int n) {
    int i,j;
    double res;
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            double r1 = sin( (pow(x,i) + pow(x,j)/2) );
            double r2 = 1 - cos( (pow(x,i) + pow(x,j))/2 );
            res += r1 * r2;
        }
    }
    return res;
}

int main(int argc,char** argv) {

    


    return 0;
}
