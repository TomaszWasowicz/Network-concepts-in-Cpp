#include <iostream>
#include <asio.hpp>

using asio::ip::udp;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: udp_client <host> <port> <message>" << std::endl;
        return 1;
    }

    try {
        asio::io_service io_service;

        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), argv[1], argv[2]);
        udp::endpoint receiver_endpoint = *resolver.resolve(query);

        udp::socket socket(io_service);
        socket.open(udp::v4());

        std::string message = argv[3];
        socket.send_to(asio::buffer(message), receiver_endpoint);

        char reply[1024];
        udp::endpoint sender_endpoint;
        size_t reply_length = socket.receive_from(asio::buffer(reply, 1024), sender_endpoint);

        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
