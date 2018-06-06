#pragma once

#include <string>
#include <sstream>

using namespace std;

class messurement
{
public:
	messurement(int, int, int, string);
	~messurement();

	string get_info();
	int get_carid() { return carid; }

private:
	int carid;
	int sensorid;
	int data;
	string timestamp;

};

