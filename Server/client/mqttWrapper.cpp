#include "mqttWrapper.h"


#include <iostream>

mqttWrapper::mqttWrapper(const char* id, const char* host_, int port_) :
	mosquittopp(id), host(host_), port(port_)
{
	mosqpp::lib_init();

	int keepalive = 120;
	if (username_pw_set("sampleuser", "samplepass") != MOSQ_ERR_SUCCESS) {
		std::cout << "setting passwd failed" << std::endl;
	}
	connect_async(host.c_str(), port, keepalive);
	
	loop_start();

}

mqttWrapper::~mqttWrapper()
{

	loop_stop();

	mosqpp::lib_cleanup();

}

void mqttWrapper::on_connect(int rc)
{
	std::cout << "Connected with code " << rc << "." << std::endl;

	if (rc == 0)
	{
		subscribe(NULL, "command/IGot");
	}

}

void mqttWrapper::myPublish(std::string topic, std::string value) {
	int ret = publish(NULL, topic.c_str(), value.size(), value.c_str(), 1, false);
	if (ret != MOSQ_ERR_SUCCESS) {
		std::cout << "Sending failed." << std::endl;
	}
}

void mqttWrapper::on_publish(int mid) {
	std::cout << "Published message with id: " << mid << std::endl;
	
}



void mqttWrapper::on_message(const mosquitto_message* message)
{
	cout << " received message of topic: " << message->topic << " Data: " << reinterpret_cast<char*>(message->payload) << "\n";
}