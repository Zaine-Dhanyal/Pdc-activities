#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int PORT = 8080;

// Function to count how many times a word appears
int count_word(const char *text, const char *word) {
    int count = 0;
    const char *pos = text;

    while ((pos = strstr(pos, word)) != NULL) {
        count++;
        pos += strlen(word);
    }
    return count;
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char word[100], result[200];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept client
    client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_sock < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Read word from client
    read(client_sock, word, sizeof(word));
    printf("Received word from client: %s\n", word);

    // Hardcoded paragraph (same as client)
    const char *paragraph = "Parallel programming helps in speeding up computations by dividing tasks into smaller chunks that can run simultaneously.";

    // Count occurrences
    int count = count_word(paragraph, word);

    // Create response
    if (count > 0) {
        snprintf(result, sizeof(result), " The word '%s' occurs %d times.", word, count);
    } else {
        snprintf(result, sizeof(result), " The word '%s' was not found in the paragraph.", word);
    }

    // Send result back
    send(client_sock, result, strlen(result), 0);

    printf("Result sent to client.\n");

    close(client_sock);
   
    return 0;
}
