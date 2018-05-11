#pragma once

#include <vector>


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


private:
	vector<Sensor*> sensors;
};

