#include <cstdio>

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <vector>

#include "ServerInst.h"

using boost::asio::ip::udp;

using namespace std;

int main(int argc, char* argv[])
{

	vector<thread*> Threads;
	vector<ServerInst*> Servers;

	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: Server <port> <amount of sensors>\n";
			return 1;
		}

		for (size_t i = 0; i < atoi(argv[2]); i++)
		{

			Servers.push_back(new ServerInst(argv[1]));
			Threads.push_back(new thread(ServerInst::run, Servers.at(i)));

		}

		for (size_t i = 0; i < Threads.size(); i++)
		{

			if (Threads.at(i)->joinable())
			{
				Threads.at(i)->join();
			}

		}

		return 0;
	}

	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}


}