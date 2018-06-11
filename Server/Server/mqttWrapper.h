#pragma once


#include "mosquittopp.h"
#include <string>

using namespace std;

class mqttWrapper: public mosqpp::mosquittopp
{
public:
	mqttWrapper(const char *id, const char *host, int port);
	~mqttWrapper();

	void on_connect(int rc);
	void on_publish(int mid);
	void on_message(const struct mosquitto_message * message);

	void myPublish(std::string topic, std::string value);

private:

	string host;
	int port;

};

