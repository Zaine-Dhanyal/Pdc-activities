#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define services 3

//int services[3]={7,8,9}
sem_t service_semaphore;
void* use_services(void* arg){
  int customer_id = *((int*)arg);
  int service_id=*((int*)arg);
 // int done=0;
printf("Customer %d wants to use a service %d...\n", customer_id, service_id);
sem_wait(&service_semaphore);
//while(!done){
printf("Customer %d is using a service %d...\n", customer_id, service_id);
sleep(2);
printf("Customer %d is done with the service %d..\n", customer_id, service_id);
//}
//done=1;
sem_post(&service_semaphore);

}

int main(){
    pthread_t customers[6];
    int customer_ids[]={1,2,3,4,5,6};
    int service_ids[]={1,2,1,3,1,2};
sem_init(&service_semaphore, 0,services );

for (int i = 0; i < 6; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, use_services, &customer_ids[i]);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(customers[i], NULL);
    }
    return 0;
}
