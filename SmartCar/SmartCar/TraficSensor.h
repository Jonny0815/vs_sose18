#pragma once
#include "Sensor.h"
class TraficSensor :
	public Sensor
{
public:
	TraficSensor();
	~TraficSensor();

	void send();
};

