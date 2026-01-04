#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 100; // shared resource
void* withdraw(void* arg) {
    int amount = *(int*)arg;
    if (balance >= amount) { 
        printf("Thread %ld: Trying to withdraw %d\n", pthread_self(), amount);
        usleep(100);
        balance -= amount;
        printf("Thread %ld: Withdrawal successful. New balance: %d\n", pthread_self(), balance);
    } else {
        printf("Thread %ld: Insufficient balance\n", pthread_self());
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int amount = 80;

    pthread_create(&t1, NULL, withdraw, &amount);
    pthread_create(&t2, NULL, withdraw, &amount);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Balance: %d\n", balance);
    return 0;
}
