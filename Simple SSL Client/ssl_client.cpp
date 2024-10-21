#include "ssl_client.h"
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>


ssl_client::ssl_client(boost::asio::io_context& io_context,
	boost::asio::ssl::context& ssl_context,
	const tcp::resolver::results_type& endpoints,
	char* message) : socket(io_context, ssl_context)
{
	memset(sendBuffer, '\0', max_length + 1);
	memset(recvBuffer, '\0', max_length + 1);
	memcpy(sendBuffer, message, strlen(message));

	socket.set_verify_mode(boost::asio::ssl::verify_peer);
	socket.set_verify_callback(
		std::bind(&ssl_client::verify_certificate, this,
			std::placeholders::_1, std::placeholders::_2));
	start(endpoints);
}

bool ssl_client::verify_certificate(bool preverified,
	boost::asio::ssl::verify_context& ctx)
{
	char subject_name[256];
	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
	//std::cout << "Verifying " << subject_name << "\n";
	return preverified;
}

void ssl_client::start(const tcp::resolver::results_type& endpoints)
{
	//Step 1: connect to the server
	boost::asio::async_connect(socket.lowest_layer(), endpoints,
		boost::bind(&ssl_client::handle_connect, this, boost::asio::placeholders::error));
}

void ssl_client::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		//Step 2: Connect success
		socket.async_handshake(boost::asio::ssl::stream_base::client,
			boost::bind(&ssl_client::handle_handshake, this, boost::asio::placeholders::error));
	}
	else
	{
		std::cout << "Connect failed: " << error.message() << "\n";
	}
}

void ssl_client::handle_handshake(const boost::system::error_code & error)
{
	if (!error)
	{
		//Step 3: hand shake success
		size_t length = std::strlen(sendBuffer);
		boost::asio::async_write(socket, boost::asio::buffer(sendBuffer, length),
			boost::bind(&ssl_client::handle_write, this,
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		std::cout << "Handshake failed: " << error.message() << '\n';
	}
}

void ssl_client::handle_write(const boost::system::error_code& error, std::size_t length)
{
	if (!error)
	{
		//Step 4: write the server success
		boost::asio::async_read(socket, boost::asio::buffer(recvBuffer, length),
			boost::bind(&ssl_client::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		std::cout << "Write failed: " << error.message() << "\n";
	}
}

void ssl_client::handle_read(const boost::system::error_code & error, std::size_t length)
{
	if (!error)
	{
		// Step 5: read from server success
		std::cout << "Reply: " << recvBuffer << std::endl;
	}
	else
	{
		std::cout << "Read failed: " << error.message() << "\n";
	}
}