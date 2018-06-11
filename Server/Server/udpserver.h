#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "messurement.h"
#include "mqttWrapper.h"

using boost::asio::ip::udp;
using namespace std;

class udpserver
{
public:
	udpserver(boost::asio::io_service&, short, mqttWrapper*);
	~udpserver();

	void handle_receive_from(const boost::system::error_code&, size_t);
	void handle_send_to(const boost::system::error_code&, size_t);

	vector<messurement*>* get_messurements() { return messurements; }

private:

	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	char data_[max_length];

	vector<messurement*>* messurements = new vector<messurement*>();
	mqttWrapper* mqtt;

};

