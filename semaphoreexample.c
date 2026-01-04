#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_COMPUTERS 5

sem_t computer_semaphore;

void* use_computer(void* arg) {
    char* name = (char*)arg;
    printf("%s wants to use a computer.\n", name);

    sem_wait(&computer_semaphore); // Wait for a free computer
    printf("%s is using a computer...\n", name);
    sleep(2); // Simulate usage
    printf("%s is done with the computer.\n", name);

    sem_post(&computer_semaphore); // Free the computer
    return NULL;
}

int main() {
    pthread_t threads[10];
    char* students[] = {"Student1","Student2","Student3","Student4","Student5",
                        "Student6","Student7","Student8","Student9","Student10"};

    sem_init(&computer_semaphore, 0, NUM_COMPUTERS);

    for(int i = 0; i < 10; i++)
        pthread_create(&threads[i], NULL, use_computer, (void*)students[i]);

    for(int i = 0; i < 10; i++)
        pthread_join(threads[i], NULL);
 
    sem_destroy(&computer_semaphore);
    return 0;
}
 