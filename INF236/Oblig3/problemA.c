#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void radixSort(int *a, int n, int b) {
    int noBuckets = 1 << b;

    //Find biggest integer max
    int max = a[0];
    int i;
    for(i=1; i<n; i++) {
        if(max < a[i]) max = a[i];
    }
    printf("Largest element in array is %d\n", max);

    int buckets[noBuckets];
    int tmp[n];

    int cntr = 0;
    while( (max >> (cntr * b)) > 0) {

        memset(buckets, 0, sizeof(buckets));
        
        //Counting the number of keys in each bucket
        for(i=0; i<n; i++) {
            int c = (a[i] >> (cntr*b) & (noBuckets-1));
            buckets[c]++;
        }

        //Prefix sum
        for(i=1; i<noBuckets; i++) {
            buckets[i] += buckets[i-1];
        }

        for(i=n-1; i>=0; i--) {
            int c = (a[i] >> (cntr*b) & (noBuckets-1));
            tmp[--buckets[c]] = a[i];
        }

        /*for(i=0; i<n; i++) {
            a[i] = tmp[i];
        }*/
        memcpy(a,tmp,n*sizeof(int));

        cntr++;

    }
}

int main(int argc, char** argv) {

    int n,b;
   
    if(argc != 3) {
        printf("Need 2 arguments, n and b\n");
        return 0;
    }

    n = atoi(argv[1]);
    b = atoi(argv[2]);

    int a[n];
    //Populate array with random numbers
    srand(time(NULL));
    int i;
    for(i=0; i<n; i++) {
        a[i] = rand() % n;
        printf("%d ", a[i]);
    }
    printf("\n");

    radixSort(a,n,b);

    printf("Sorted array\n");
    for(i=0; i<n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
