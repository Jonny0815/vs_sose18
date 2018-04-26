#pragma once

#include <vector>
#include <thread>
#include <random>

#include "Sensor.h"
#include "TraficSensor.h"
#include "DistanceSensor.h"
#include "SpeedSensor.h"
#include "FuelSensor.h"

using namespace std;

class Car
{
public:
	Car();
	~Car();

	void drive();

private:
	vector<Sensor*> sensors;
	vector<thread*> threads;

	int id;
};

