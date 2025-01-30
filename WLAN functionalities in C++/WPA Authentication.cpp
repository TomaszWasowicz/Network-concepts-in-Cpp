/*
To connect to a Wi-Fi network using WPA2, 
we communicate with wpa_supplicant, 
the Linux Wi-Fi authentication daemon.

Steps to Connect:

1. Use a Unix socket to talk to wpa_supplicant.
2. Send commands like ADD_NETWORK, SET_NETWORK, and ENABLE_NETWORK.
3. Monitor wpa_supplicant for connection status.

How It Works:

- Sends WPA2 authentication requests
- Uses wpa_supplicant for encryption
- Can be extended for WPA-Enterprise (EAP)

Run It

g++ -o wpa_auth wpa_auth.cpp
sudo ./wpa_auth

Note: Ensure wpa_supplicant is running.

*/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define WPA_CTRL_PATH "/var/run/wpa_supplicant/wlan0"  // Change interface name if needed

void send_command(int sock, const std::string& cmd) {
    send(sock, cmd.c_str(), cmd.size(), 0);
    char buffer[256];
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    std::cout << "Response: " << buffer << std::endl;
}

int main() {
    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    struct sockaddr_un addr {};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, WPA_CTRL_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to connect to wpa_supplicant\n";
        return 1;
    }

    send_command(sock, "ADD_NETWORK");
    send_command(sock, "SET_NETWORK 0 ssid \"MySSID\"");
    send_command(sock, "SET_NETWORK 0 psk \"MyPassword\"");
    send_command(sock, "ENABLE_NETWORK 0");

    std::cout << "WPA Authentication initiated...\n";
    close(sock);
    return 0;
}
