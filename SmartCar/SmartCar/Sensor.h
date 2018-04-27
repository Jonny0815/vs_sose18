#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>


using boost::asio::ip::udp;

class Sensor
{
public:
	Sensor(char*,char*,int, int);
	~Sensor();

	void send();


private:

	int id;
	char *host;
	char *port;
	int amount_sends;
	int carid;

};

