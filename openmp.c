#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<sys/time.h>


#define num 10000000
int*a; //Dynamic arrays for data storage
int*b;
int*c;

int main(){
    struct timeval s_start, s_end, p_start, p_end;
  //serial version 

gettimeofday(&s_start, NULL);
a = malloc(num * sizeof(int));
b = malloc(num * sizeof(int));
c = malloc(num * sizeof(int));

for (int i = 0; i < num; i++) {
    a[i] = rand() % 10000;
    b[i] = rand() % 10000;
    c[i] = 0;
}
gettimeofday(&s_end, NULL);
double s_time=(s_end.tv_sec-s_start.tv_sec)+(s_end.tv_usec-s_start.tv_usec)/1000000.0;




//parallel version
 gettimeofday(&p_start, NULL); 
  long int sum=0; //shared public variable 

 #pragma omp parallel num_threads(16)
 {

    #pragma omp for reduction(+:sum)
for(int i=0; i<num; i++){
    c[i]=a[i]*b[i];
sum=sum+c[i];
}

}
 gettimeofday(&p_end, NULL);  

double p_time=(p_end.tv_sec-p_start.tv_sec)+(p_end.tv_usec-p_start.tv_usec)/1000000.0;

printf("SUM %ld \nS TIME:%f sec\nP TIME:%f sec\nTOTAL TIME:%f\n",sum, s_time,p_time,s_time+p_time);

}