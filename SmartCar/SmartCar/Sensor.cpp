#include "Sensor.h"



Sensor::Sensor(char* host_h, char* port_h, int amount_sends_h, int carid_h)
{
	

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

	for (size_t i = 0; i < amount_sends; i++)
	{
		string data_s = to_string(carid) + " " + to_string(id) + " " + to_string(rand() % 100);

		strncpy(data, data_s.c_str(), 1024);

		size_t request_length = strlen(data);
		s.send_to(boost::asio::buffer(data, request_length), *iterator);

		cout << id << " " << carid << "sending" << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}


	// todo zähl angekommene packete, evtl verloren ? + TIMESTAMPS !!!
	
}
catch (std::exception& e)
{
	std::cerr << "Exception: " << e.what() << "\n";
}



}

