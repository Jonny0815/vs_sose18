#include <cstdio>

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <vector>

#include "ServerInst.h"

using boost::asio::ip::udp;

using namespace std;

int main(int argc, char* argv[])
{


	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: Server <port> <amount of sensors>\n";
			return 1;
		}

		boost::asio::io_service io_service;





		ServerInst s1(argv[1]);
		s1.run_udp(io_service);

		//boost::thread* thr = new boost::thread(&ServerInst::run_udp, &s1,&io_service); // not working ? neither with c++11 threads

		return 0;
	}

	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}


}