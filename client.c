#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int PORT = 8080;

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char word[100], buffer[1024] = {0};

    // Hardcoded paragraph (same as server)
    const char *paragraph = "Parallel programming helps in speeding up computations by dividing tasks into smaller chunks that can run simultaneously.";

    // Display paragraph to user
    printf("Paragraph:\n%s\n", paragraph);
    printf("\nEnter a word to count: ");
    scanf("%s", word);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect to server
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    // Send word to server
    send(sock, word, strlen(word), 0);

    // Receive result
    read(sock, buffer, sizeof(buffer));
    printf("\nServer says: %s\n", buffer);

    close(sock);
    return 0;
}
