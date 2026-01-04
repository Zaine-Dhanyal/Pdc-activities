#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void getCurrentTime(char *buffer) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 9, "%H:%M:%S", timeinfo); // format HH:MM:SS
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int master = 0;
    char dish[50];
    MPI_Status status;

    char *dishes[] = {"Burger", "Tea", "Fries", "Sandwich", "Pizza", "Biryani", "Daal"};
    int prep_times[] = {5, 2, 3, 4, 6, 7, 3};

    if (rank == master) {
        int total_orders;
        printf("Enter number of orders: ");
        fflush(stdout);
        scanf("%d", &total_orders);

        char order_list[total_orders][50];
        for (int i = 0; i < total_orders; i++) {
            printf("Enter dish name %d: ", i + 1);
            fflush(stdout);
            scanf("%s", order_list[i]);
        }

        int next_order = 0;
        int completed_orders = 0;

        // Initially assign orders to available chefs
        for (int w = 1; w < size && next_order < total_orders; w++) {
            MPI_Send(order_list[next_order], 50, MPI_CHAR, w, 2, MPI_COMM_WORLD);
            char timeStr[9];
            getCurrentTime(timeStr);
            printf("[MASTER] Time %s: Assigned '%s' to Chef %d 🍽️\n", timeStr, order_list[next_order], w);
            next_order++;
        }

        // Now handle chefs as they get free
        while (completed_orders < total_orders) {
            int free_chef;
            MPI_Recv(&free_chef, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            completed_orders++;

            if (next_order < total_orders) {
                MPI_Send(order_list[next_order], 50, MPI_CHAR, free_chef, 2, MPI_COMM_WORLD);
                char timeStr[9];
                getCurrentTime(timeStr);
                printf("[MASTER] Time %s: Chef %d is free → New dish '%s' assigned 🍛\n",
                       timeStr, free_chef, order_list[next_order]);
                next_order++;
            } else {
                strcpy(dish, "stop");
                MPI_Send(dish, 50, MPI_CHAR, free_chef, 2, MPI_COMM_WORLD);
            }
        }

        printf("\n✅ All orders completed successfully!\n");
    } 
    else {
        // Worker (Chef)
        char current_dish[50];
        while (1) {
            MPI_Recv(current_dish, 50, MPI_CHAR, master, 2, MPI_COMM_WORLD, &status);
            if (strcmp(current_dish, "stop") == 0)
                break;

            int time_needed = 3;
            for (int i = 0; i < 7; i++) {
                if (strcmp(current_dish, dishes[i]) == 0)
                    time_needed = prep_times[i];
            }

            char timeStr[9];
            getCurrentTime(timeStr);
            printf("⏱️  Time %s: Chef %d started '%s' (will take %d sec)\n",
                   timeStr, rank, current_dish, time_needed);
            fflush(stdout);

            sleep(time_needed);

            getCurrentTime(timeStr);
            printf("✅  Time %s: Chef %d completed '%s'\n",
                   timeStr, rank, current_dish);
            fflush(stdout);

            MPI_Send(&rank, 1, MPI_INT, master, 1, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
