#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BROADCAST_IP "255.255.255.255"
#define BUFFER_SIZE 512

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    char buffer[BUFFER_SIZE];
    int broadcast_enable = 1;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to enable broadcasting
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        perror("Error in setting broadcast option");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Setup the broadcast address
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    // Broadcast loop
    while (1) {
        printf("Enter message to broadcast (type 'QUIT' to exit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        // Send broadcast message
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Sendto failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // Exit if the user types "QUIT"
        if (strcmp(buffer, "QUIT") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
