#pragma once

#include <vector>
#include <thread>
#include <random>

#include "Sensor.h"


using namespace std;

class Car
{
public:
	Car(char*, char*,int);
	~Car();

	void drive();

private:
	vector<Sensor*> sensors;
	vector<thread*> threads;

	int id;
	char *host;
	char *port;
	int amount_sends;
};

