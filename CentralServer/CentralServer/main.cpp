#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <vector>


using boost::asio::ip::udp;

using namespace std;

int main(int argc, char* argv[])
{

	vector<*thread> Threads;
	vector<*Server> Servers;

	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: Server <port> <amount of sensors>\n";
			return 1;
		}

		for (size_t i = 0; i < atoi(argv[2]); i++)
		{

			Servers.push_back(new Server(argv[1]));
			Threads.push_back(new thread(Server::run, Servers.at(i)));

		}

		for (size_t i = 0; i < Threads.size(); i++)
		{

			if (Threads.at(i).joinable())
			{
				Threads.at(i).join();
			}

		}

    return 0;
}