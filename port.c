#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void scan_port(const char *ip, int port) {
    int sock;
    struct sockaddr_in target;

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define target IP and port
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip, &target.sin_addr);

    // Attempt to connect to the target IP and port
    if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
        printf("Port %d is open\n", port);
    } else {
        printf("Port %d is closed\n", port);
    }

    // Close the socket
    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if (start_port <= 0 || end_port <= 0 || start_port > end_port) {
        fprintf(stderr, "Invalid port range.\n");
        return 1;
    }

    printf("Scanning IP: %s, Ports: %d - %d\n", ip, start_port, end_port);

    for (int port = start_port; port <= end_port; port++) {
        scan_port(ip, port);
    }

    return 0;
}
