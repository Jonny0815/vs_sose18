#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>


#include "Car.h"




using namespace std;

using boost::asio::ip::udp;

int main(int argc, char *argv[])
{

	vector<Car*> cars;

	if (argc != 5)
	{
		std::cerr << "Usage: SmartCar <host> <port> <number of cars> <amount of outgoing messurements per sensor>\n";
		return 1;
	}

	
	for (size_t i = 0; i < atoi(argv[3]); i++)
	{
		cars.push_back(new Car(argv[1], argv[2], atoi(argv[4])));
	}

	for (size_t i = 0; i < cars.size(); i++)
	{
		cars.at(i)->drive();
	}

	
    return 0;
}