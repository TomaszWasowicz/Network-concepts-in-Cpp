#include <iostream>
#include "EchoGetPostWS.h"

using namespace std;
using namespace restbed;

int ws_port;
std::string ws_path;

void post_method_handler(const shared_ptr<Session> session)
{
	const auto request = session->get_request();
	int content_length = 0;

	request->get_handler("Content-Length", content_lenght, 0);
	std::cout << "HTTP POST Request received content_length : " << content_length << std::endl;
	session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes& body)
		{
			const auto request = session->get_request();
			int content_length = 0;
			request->get_header("Content-Length", content_length, 0);

			std::stringstream myStream;
			myStream << "{\r\n";
			myStream << "	'WS port' : '" << ws_port << "',\r\n	'WS path' : '" << ws_path << "',\r\n";
			myStream << "	'http_request' : 'POST',\r\n";
			myStream << "	'Content-Length' : '" << content_length << "',\r\n";
			myStream << "	" << std::string(body.begin(), body.end()) << "\r\n";
			myStream << std::string(body.begin(), body.end()) << std::endl;

			//parseBodyToBsonDoc(bodyStr);

			std::string bodyStr = myStream.str();
			std::string response_body = "Body-Length is : " + std::to_string(bodyStr.length());
			session->close(OK, bodyStr, { { "Content-Length", std::to_string(bodyStr.length())} });
		});
}
