#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Mutex for blender
pthread_mutex_t blender_mutex;

void* use_blender(void* arg) {
    char* name = (char*)arg;
    printf("%s wants to use the blender.\n", name);

    pthread_mutex_lock(&blender_mutex); // Lock the blender
    printf("%s is using the blender...\n", name);
    sleep(2); // Simulate usage
    printf("%s is done with the blender.\n", name);

    pthread_mutex_unlock(&blender_mutex); // Unlock
    return NULL;
}

int main() {
    pthread_t threads[3];
    char* girls[] = {"Alice", "Bella", "Clara"};

    pthread_mutex_init(&blender_mutex, NULL);

    for(int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, use_blender, (void*)girls[i]);

    for(int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&blender_mutex);
    return 0;
}
