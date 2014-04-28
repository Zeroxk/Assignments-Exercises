#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    if(argc != 4) {
        printf("Input n, b and np\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int b = atoi(argv[2]);
    int np = atoi(argv[3]);

    omp_set_num_threads(np);

    int A[n];
    //Populate array with random numbers
    srand(time(NULL));
    int i;
    for(i=0; i<n; i++) {
        A[i] = rand() % n;
    }

    return 0;
}
