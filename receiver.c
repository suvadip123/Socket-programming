#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 512

int main() {
    int sockfd;
    struct sockaddr_in recv_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup the receiver address
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Listening for broadcast messages...\n");

    // Receive loop
    while (1) {
        addr_len = sizeof(recv_addr);
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv_addr, &addr_len) < 0) {
            perror("Recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("Received: %s\n", buffer);

        // Exit if the received message is "QUIT"
        if (strcmp(buffer, "QUIT") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
