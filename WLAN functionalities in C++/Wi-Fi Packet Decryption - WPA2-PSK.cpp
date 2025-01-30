/*

This example decrypts WPA2-encrypted Wi-Fi packets captured with libpcap.

Requirements:
1. libpcap (packet capture)
2. OpenSSL AES (for decryption)

How It Works
- Captures Wi-Fi packets via libpcap
- Uses OpenSSL AES to decrypt WPA2 frames
- Prints decrypted data

Compile & Run: 

g++ -o decrypt_wpa decrypt_wpa.cpp -lpcap -lssl -lcrypto
sudo ./decrypt_wpa

Note: This requires knowledge of the WPA2-PSK.

*/

#include <iostream>
#include <pcap.h>
#include <openssl/aes.h>
#include <cstring>

// Replace with your WPA2-PSK key
const uint8_t WPA2_KEY[32] = { 0xAB, 0xCD, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC,
                               0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
                               0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE,
                               0xFF, 0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC };

void decrypt_wpa2_packet(const uint8_t* data, size_t length) {
    uint8_t decrypted[256];
    AES_KEY aes_key;
    AES_set_decrypt_key(WPA2_KEY, 256, &aes_key);
    AES_decrypt(data, decrypted, &aes_key);

    std::cout << "Decrypted Packet: ";
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", decrypted[i]);
    }
    std::cout << std::endl;
}

void packet_handler(u_char* user, const struct pcap_pkthdr* hdr, const u_char* packet) {
    std::cout << "Captured Wi-Fi packet of size " << hdr->len << "\n";
    decrypt_wpa2_packet(packet, hdr->len);
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live("wlan0", BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        std::cerr << "Failed to open device: " << errbuf << "\n";
        return 1;
    }

    std::cout << "Capturing WPA2 packets...\n";
    pcap_loop(handle, 10, packet_handler, nullptr);

    pcap_close(handle);
    return 0;
}
