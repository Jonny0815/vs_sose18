#include "session.h"



session::session(boost::asio::io_service& io_service)
	: socket_(io_service)
{
}



session::~session()
{
}

tcp::socket& session::socket()
{
	return socket_;
}

void session::start()
{
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
		boost::bind(&session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	if (!error)
	{

		std::string data_s = "HTTP/1.1 200 OK \r\n Date: Mon, 27 Jul 2009 12:28:53 GMT \r\n Server: Apache/2.2.14 (Win32) \r\n Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT \r\n Content-Length: 88 \r\n Content-Type: text/html \r\n Connection: Closed \r\n";


		strncpy(data_, data_s.c_str(), 1024);

		std::cout << data_;

		boost::asio::async_write(socket_,
			boost::asio::buffer(data_, bytes_transferred),
			boost::bind(&session::handle_write, this,
				boost::asio::placeholders::error));
	}
	else
	{
		delete this;
	}
}

void session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{

		std::cout << data_;

		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		delete this;
	}
}