#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <iostream>
#include <asio.hpp> // Standalone ASIO
#include <string>

using asio::ip::udp;

class myUdpServer
{
public:
    myUdpServer(asio::io_service& io_service, short port)
        : socket_(io_service, udp::endpoint(udp::v4(), port))
    {
        my_udp_receive();
    }

    void my_udp_receive()
    {
        socket_.async_receive_from(asio::buffer(data_, max_length), sender_endpoint_,
            [this](std::error_code ec, std::size_t recvd_bytes) {
                if (!ec && recvd_bytes > 0) {
                    std::cout << "[" << recvd_bytes << "] " << data_ << std::endl;
                    my_udp_send_back();
                }
                else {
                    my_udp_receive();
                }
            });
    }

    void my_udp_send_back()
    {
        std::string myStr = "Sender endpoint: " + sender_endpoint_.address().to_string() +
            " port: " + std::to_string(sender_endpoint_.port()) +
            " Message: " + data_;
        socket_.async_send_to(asio::buffer(myStr.c_str(), myStr.length()), sender_endpoint_,
            [this](std::error_code /*ec*/, std::size_t /*sent_bytes*/) {
                my_udp_receive();
            });
    }

private:
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum { max_length = 1024 };
    char data_[max_length];
};

#endif
