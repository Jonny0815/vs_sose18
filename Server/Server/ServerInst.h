#pragma once


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

using namespace std;

class ServerInst
{
public:
	ServerInst(char*);
	~ServerInst();
	void run();

private:

	int port;

	int carid;
	int id;
	vector<int> messurements;
	int recieved_messurements;

};

