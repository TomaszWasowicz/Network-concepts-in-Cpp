#include "udp_server.hpp"
#include <iostream>
#include <asio.hpp>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: udp_server <port>" << std::endl;
        return 1;
    }

    try {
        asio::io_service io_service;
        myUdpServer server(io_service, std::atoi(argv[1]));
        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
