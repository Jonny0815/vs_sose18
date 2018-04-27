#include "Sensor.h"



Sensor::Sensor(char* host_h, char* port_h, int amount_sends_h, int carid_h)
{
	srand(time(NULL));

	carid = carid_h;
	id = rand() % 1024;
	host = host_h;
	port = port_h;
	amount_sends = amount_sends_h;

}

Sensor::~Sensor()
{
}

void Sensor::send()
{

	try{

	boost::asio::io_service io_service;

	udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), host, port);
	udp::resolver::iterator iterator = resolver.resolve(query);

	using namespace std; // For strlen.
	char data[1024];
	string data_s;
	

	


	//sending data here
	size_t request_length = strlen(data);
	s.send_to(boost::asio::buffer(data, request_length), *iterator);

	
}
catch (std::exception& e)
{
	std::cerr << "Exception: " << e.what() << "\n";
}



}

