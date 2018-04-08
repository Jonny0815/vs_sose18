#include "Car.h"

Car::Car(){

	sensors.push_back(new SpeedSensor);
	sensors.push_back(new FuelSensor);
	sensors.push_back(new DistanceSensor);
	sensors.push_back(new TraficSensor);



}

Car::~Car(){


}