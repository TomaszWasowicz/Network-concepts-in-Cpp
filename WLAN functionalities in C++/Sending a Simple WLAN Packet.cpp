/*

This example shows how to send a raw 802.11 Wi-Fi frame using a socket.

Features:
- Sends a basic WLAN frame
- Uses raw sockets for direct access
*/

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <unistd.h>

#define WLAN_FRAME_SIZE 256

int main() {
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        std::cerr << "Failed to create raw socket\n";
        return 1;
    }

    struct sockaddr_ll device;
    struct ifreq ifr;
    memset(&device, 0, sizeof(device));
    memset(&ifr, 0, sizeof(ifr));

    // Specify the interface to use
    strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        std::cerr << "Cannot find interface wlan0\n";
        return 1;
    }

    device.sll_ifindex = ifr.ifr_ifindex;
    device.sll_protocol = htons(ETH_P_ALL);

    // Dummy WLAN frame
    uint8_t frame[WLAN_FRAME_SIZE] = { 0 };
    frame[0] = 0x08; // Frame control (Beacon Frame)

    if (sendto(sock, frame, WLAN_FRAME_SIZE, 0, (struct sockaddr*)&device, sizeof(device)) < 0) {
        std::cerr << "Failed to send packet\n";
        return 1;
    }

    std::cout << "WLAN Packet sent!\n";

    close(sock);
    return 0;
}
