#pragma once
#include "Sensor.h"
class FuelSensor :
	public Sensor
{
public:
	FuelSensor();
	~FuelSensor();

	void send();
};

