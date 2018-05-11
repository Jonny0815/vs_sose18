#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session
{
public:
	Session(boost::asio::io_service&);
	~Session();

	tcp::socket& socket();
	void start();


private:
	
	void handle_write(const boost::system::error_code&);
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	
	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

