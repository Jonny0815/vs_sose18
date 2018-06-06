#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>

#include "messurement.h"

using boost::asio::ip::tcp;

using namespace std;

class Session
{
public:
	Session(boost::asio::io_service&, vector<messurement*>*);
	~Session();

	tcp::socket& socket();
	void start();


private:
	
	void handle_write(const boost::system::error_code&);
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	
	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];

	vector<messurement*>* messurements;
};

