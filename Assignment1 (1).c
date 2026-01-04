
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

int main() {
    
    long sizes[] = {100000, 500000, 1000000, 5000000, 10000000, 
                    50000000, 100000000, 500000000, 1000000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    for (int i = 0; i < numSizes; i++) {
        long n = sizes[i];
        printf("\nRunning for input size: %ld\n", n);
        clock_t start = clock();
        float *arr = (float *)malloc(n * sizeof(float));
        if (arr == NULL) {
            printf("Memory allocation failed for size %ld\n", n);
            continue;
        }

        for (long j = 0; j < n; j++) {
            arr[j] = random_float();
        }
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Execution Time: %f seconds\n", time_taken);

        free(arr);
    }
    return 0;
}


