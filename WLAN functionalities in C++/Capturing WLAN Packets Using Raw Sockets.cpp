/*
This C++ example demonstrates how to capture Wi-Fi (802.11) frames using raw sockets on Linux.
It listens to incoming packets from a Wi-Fi interface (e.g., wlan0).

Compile with:

g++ -o wlan_sniffer wlan_sniffer.cpp -lpcap

Run with:

sudo ./wlan_sniffer

Features:
- Captures raw WLAN packets
- Uses libpcap to listen on wlan0
- Extracts Ethernet and IP headers

*/

#include <iostream>
#include <pcap.h>
#include <netinet/if_ether.h> // Ethernet headers
#include <netinet/ip.h>       // IP headers
#include <netinet/tcp.h>      // TCP headers

void packetHandler(u_char* user, const struct pcap_pkthdr* pktHeader, const u_char* packet) {
    struct ethhdr* eth = (struct ethhdr*)packet;

    std::cout << "\nCaptured Packet: " << pktHeader->len << " bytes\n";

    // Check if it's an IP packet
    if (ntohs(eth->h_proto) == ETH_P_IP) {
        struct iphdr* ip = (struct iphdr*)(packet + sizeof(struct ethhdr));
        std::cout << "IP Packet: Source IP: " << ((ip->saddr) & 0xFF) << "."
            << ((ip->saddr >> 8) & 0xFF) << "." << ((ip->saddr >> 16) & 0xFF) << "."
            << ((ip->saddr >> 24) & 0xFF) << "\n";
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* alldevs;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << "\n";
        return 1;
    }

    // Open device for sniffing
    pcap_t* handle = pcap_open_live("wlan0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        std::cerr << "Could not open device wlan0\n";
        return 1;
    }

    std::cout << "Listening on wlan0...\n";
    pcap_loop(handle, 10, packetHandler, NULL);

    pcap_close(handle);
    return 0;
}
