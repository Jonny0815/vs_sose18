#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class session
{
public:
	session(boost::asio::io_service&);
	tcp::socket& socket();
	void start();

private:
	void handle_read(const boost::system::error_code&, size_t);
	void handle_write(const boost::system::error_code&);

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};


