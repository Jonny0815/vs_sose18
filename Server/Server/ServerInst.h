#pragma once


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>


using boost::asio::ip::udp;
using boost::asio::ip::tcp;

using namespace std;

class ServerInst
{
public:
	ServerInst(char*);
	~ServerInst();
	void run_udp(boost::asio::io_service&);
	void run_http(boost::asio::io_service&);

private:

	int port;
	vector<string> messurements;
	int recieved_messurements;

};

