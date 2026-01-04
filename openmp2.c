#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<sys/time.h>
int main(){

#pragma omp parallel  num_threads(4)
{
    // #pragma omp for schedule (static,10) //(this will happening on the compile time)
    //   #pragma omp for schedule (dynamic,10) //(this will happening on the run time)
      #pragma omp for schedule (guided,2) //(chunks)
for(int i=0; i<20; i++){

    int tid=omp_get_thread_num();
    // int tid=1;
    printf("Thread %d is working on iteration %d\n",tid,i);
}
}


}