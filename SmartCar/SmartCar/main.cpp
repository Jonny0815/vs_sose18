#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>


#include "Car.h"




using namespace std;

using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: SmartCar <host> <port>\n";
		return 1;
	}

	


	Car c(argv[1],argv[2]);
	

	



    return 0;
}