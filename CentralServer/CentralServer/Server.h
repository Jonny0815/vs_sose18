#pragma once

#include <cstdlib>
#include <iostream>
#inclulde <vector>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

using namepace std;

class Server
{
public:
	Server(char*);
	~Server();

	void run();


private:
	int port;

	int carid;
	int id;
	vector<int> messurements;
	int recieved_messurements;

};

