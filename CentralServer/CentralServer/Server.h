#pragma once

#include <iostream>

#include <boost\asio.hpp>
#include <boost\array.hpp>


using namespace std;
using boost::asio::ip::udp;

class Server
{
public:
	Server();
	~Server();
};

