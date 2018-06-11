#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <boost/thread.hpp>

#include "ServerInst.h"

#include "tcpserver.h"
#include "udpserver.h"
#include "mqttWrapper.h"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

using namespace std;


int main(int argc, char* argv[])
{


	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: Server <port udp/tcp> <mqtt host>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		mqttWrapper* mqtt;
		mqtt = new mqttWrapper("test1337", argv[2], 1883);
		
		udpserver udps(io_service, atoi(argv[1]), mqtt);
		tcpserver tcps(io_service, atoi(argv[1]), udps.get_messurements());

		io_service.run();



		// blocking udp Server, no in use anymore

		//ServerInst s1(argv[1]);
		//s1.run_udp(io_service);

		//boost::thread* thr = new boost::thread(&ServerInst::run_udp, &s1,&io_service); // not working ? neither with c++11 threads

		return 0;
	}

	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}


}







