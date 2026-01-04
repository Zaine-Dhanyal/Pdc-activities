#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <semaphore.h>

int flags[3] = {0,0,0};//0 means free  

char* files[3] = {"f1.txt","f2.txt","f3.txt"};
sem_t writing_sem;
void* thread_write(void* args){

    int write_token = *(int*)args;
    int done = 0;
    
    sem_wait(&writing_sem);
    printf("Thread- %d Start %ld\n",write_token,time(NULL));
    while(!done)
        for(int i=0;i<3;i++){
            //usleep(rand()%50000);
            if(flags[i] == 0){
                
                usleep(rand()%500);
                flags[i]=1;
                
                FILE *fp;
        
                fp = fopen(files[i], "a");
                for (int lim=0;lim<100000;lim++){
                    fprintf(fp, "%d", write_token);   // write integer as text
                    usleep(20);
                }
                fprintf(fp, "%s", "\n");
                fclose(fp);
                
                done=1;
                flags[i] = 0;
                break;
            }
        }
 sem_post(&writing_sem);// using for thread 4

}
int main(void){
    pthread_t t1, t2, t3, t4;
    int as[] = {1,2,3,4};
    srand(time(NULL));
    sem_init(&writing_sem, 0, 3);
    pthread_create(&t1, NULL, thread_write, (void*)(as+0));
    pthread_create(&t2, NULL, thread_write, (void*)(as+1));
    pthread_create(&t3, NULL, thread_write, (void*)(as+2));
    pthread_create(&t4, NULL, thread_write, (void*)(as+3));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}

// prime@DESKTOP-O9B6B2S:/mnt/d/Semester 7/PDC$ gcc semaphoreexample.c -o semaphoreexample -lpthread
// prime@DESKTOP-O9B6B2S:/mnt/d/Semester 7/PDC$ ./semaphoreexample