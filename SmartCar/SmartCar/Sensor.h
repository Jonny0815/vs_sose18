#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <locale>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>


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

