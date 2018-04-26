#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>


using boost::asio::ip::udp;

class Sensor
{
public:
	Sensor();
	~Sensor();

	void send();

};

