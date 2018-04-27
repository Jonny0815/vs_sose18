#include "Server.h"




Server::Server(char* port_h)
{
	port = atoi(port_h);
}


Server::~Server()
{
}

void Server::run()
{
	boost::asio::io_service io_service;

	udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
	for (;;)
	{
		char data[1024];
		udp::endpoint sender_endpoint;
		size_t length = sock.receive_from(
			boost::asio::buffer(data, 1024), sender_endpoint);

		recieved_messurements++;

		string data_s = data;


	}





}
