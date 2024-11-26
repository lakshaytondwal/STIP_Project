#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <unistd.h>

// Function to get the current MAC address
void get_mac_address(const char *interface, char *mac) {
    int sock;
    struct ifreq ifr;

    // Create a socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Copy the interface name to the ifreq structure
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);

    // Get the current MAC address
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        perror("Failed to get MAC address");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Format the MAC address as a string
    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
            (unsigned char)ifr.ifr_hwaddr.sa_data[0],
            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

    close(sock);
}

// Function to change the MAC address
void change_mac_address(const char *interface, const char *new_mac) {
    int sock;
    struct ifreq ifr;

    // Create a socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Copy the interface name to the ifreq structure
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);

    // Set the new MAC address
    sscanf(new_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &ifr.ifr_hwaddr.sa_data[0], &ifr.ifr_hwaddr.sa_data[1], &ifr.ifr_hwaddr.sa_data[2],
           &ifr.ifr_hwaddr.sa_data[3], &ifr.ifr_hwaddr.sa_data[4], &ifr.ifr_hwaddr.sa_data[5]);
    ifr.ifr_hwaddr.sa_family = ARPHRD_ETHER;

    if (ioctl(sock, SIOCSIFHWADDR, &ifr) < 0) {
        perror("Failed to set new MAC address");
        close(sock);
        exit(EXIT_FAILURE);
    }

    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interface> <new-mac>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *interface = argv[1];
    const char *new_mac = argv[2];
    char current_mac[18];

    // Get the current MAC address
    get_mac_address(interface, current_mac);

    // Print the current MAC address
    printf("Current MAC: %s\n", current_mac);

    // Change the MAC address
    change_mac_address(interface, new_mac);

    // Get the new MAC address
    char updated_mac[18];
    get_mac_address(interface, updated_mac);

    // Print the new MAC address
    printf("New MAC: %s\n", updated_mac);

    return EXIT_SUCCESS;
}
