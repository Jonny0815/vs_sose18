#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "udp_server.h"
#include "tcp_server.h"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;



int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		udp_server udp_s(io_service, atoi(argv[1]));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
