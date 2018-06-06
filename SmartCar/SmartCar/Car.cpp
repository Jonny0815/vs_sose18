#include "Car.h"

Car::Car(char* host_h, char* port_h, int amount_sends_h){



	id = rand()%899 + 100;
	host = host_h;
	port = port_h;
	amount_sends = amount_sends_h;



	sensors.push_back(new Sensor(host, port, amount_sends, id));
	sensors.push_back(new Sensor(host, port, amount_sends, id));
	sensors.push_back(new Sensor(host, port, amount_sends, id));
}

Car::~Car(){

	for (size_t i = 0; i < threads.size(); i++)
	{
		delete threads.at(i);
	}

	for (size_t i = 0; i < sensors.size(); i++)
	{
		delete sensors.at(i);
	}

}

void Car::drive()
{
	for (size_t i = 0; i < sensors.size(); i++) //creating threads for all sensors
	{
		
		threads.push_back(new thread(&Sensor::send, sensors.at(i)));

	}

	for (size_t i = 0; i < threads.size(); i++) //joining threads
	{
		if (threads.at(i)->joinable())
		{
			threads.at(i)->join();
		}
	}
}
