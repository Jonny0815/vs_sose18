#pragma once
#include "Sensor.h"
class DistanceSensor :
	public Sensor
{
public:
	DistanceSensor();
	~DistanceSensor();

	void send();
};

