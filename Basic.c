#include <stdio.h>
#include <omp.h>
#include <time.h>
#define size 9990

int a[size];

int main(){
    // int th_id;
    // #pragma omp parallel private(th_id)
    // {
    //     th_id=omp_get_thread_num();
    // printf("Hello World %d\n",th_id);
    // }
    // printf("\n************All Done***************\n");


    for(long int i=0; i<size; i++){
                a[i]=0;
    }

    clock_t start_s, end_s, start_p, end_p;
    //serial version
start_s=clock();
for(long int i=0; i<size; i++){
               a[i]=2*a[i];
}

end_s=clock();
double duration_s=(double)(end_s-start_s)/CLOCKS_PER_SEC;
printf("The serial version took %f units \n",duration_s);





//parallel version
start_p=clock();
#pragma omp parallel for num_threads(3)
for(long int i=0; i<size; i++){
               a[i]=2*a[i];
}

end_p=clock();
double duration_p=(double)(end_p-start_p)/CLOCKS_PER_SEC;
printf("The parallel version took %f units \n",duration_p);



return 0;

}