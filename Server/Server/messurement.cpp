#include "messurement.h"



messurement::messurement(int carid_h, int sensorid_h, int data_h, std::string timestamp_h)
{

	carid = carid_h;
	sensorid = sensorid_h;
	data = data_h;
	timestamp = timestamp_h;

}


messurement::~messurement()
{
}

string messurement::get_info()
{
	stringstream to_return;

	to_return << "CarID: " << carid << "\t SensorID: " << sensorid << "\t Value: " << data << "\t Time: " << timestamp << "<br>";

	return to_return.str();
}
