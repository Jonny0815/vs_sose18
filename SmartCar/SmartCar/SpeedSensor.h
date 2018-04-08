#pragma once
#include "Sensor.h"
class SpeedSensor :
	public Sensor
{
public:
	SpeedSensor();
	~SpeedSensor();

	void send();
};

