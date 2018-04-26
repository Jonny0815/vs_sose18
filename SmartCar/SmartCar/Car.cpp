#include "Car.h"

Car::Car(char* host_h, char* port_h){

	srand(time(NULL));


	sensors.push_back(new Sensor);

	/*sensors.push_back(new SpeedSensor);
	sensors.push_back(new FuelSensor);
	sensors.push_back(new DistanceSensor);
	sensors.push_back(new TraficSensor);*/

	id = rand()%1024;
	host = host_h;
	port = port_h;

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
