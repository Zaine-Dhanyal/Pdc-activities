#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define TOTAL_TICKETS 10
#define NUM_CUSTOMERS 2

int available_tickets = TOTAL_TICKETS;
pthread_mutex_t ticket_mutex;   // mutex lock for critical section

void* book_ticket(void* arg) {
    int customer_id = *((int*)arg);

    pthread_mutex_lock(&ticket_mutex);   // lock before accessing shared data

    if (available_tickets > 0) {
        int ticket = available_tickets;
        usleep(rand() % 50000); 
        available_tickets--;
        printf("Customer %d booked ticket #%d \n", customer_id, ticket);
        
    } else {
        printf("Customer %d tried to book, but tickets are SOLD OUT \n", customer_id);
    }

    pthread_mutex_unlock(&ticket_mutex); // unlock after critical section
    return NULL;
}

int main() {
    pthread_t customers[NUM_CUSTOMERS];
    int customer_ids[NUM_CUSTOMERS];
    srand(time(NULL));
    pthread_mutex_init(&ticket_mutex, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customers[i], NULL, book_ticket, &customer_ids[i]);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    pthread_mutex_destroy(&ticket_mutex);

    printf("\nAll bookings processed. Tickets left: %d\n", available_tickets);
    return 0;
}
