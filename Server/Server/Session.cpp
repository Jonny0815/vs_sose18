#include "Session.h"



Session::Session(boost::asio::io_service& io_service)
	: socket_(io_service)
{
}


Session::~Session()
{
}


tcp::socket& Session::socket()
{
	return socket_;
}

void Session::start()
{
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
		boost::bind(&Session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}


void Session::handle_read(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	if (!error)
	{

		std::string data_s = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nContent-Length: 88\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html>\r\n<body>\r\n<h1>Hello, World!</h1>\r\n</body>\r\n</html>";
		strncpy(data_, data_s.c_str(), 1024);
		

		boost::asio::async_write(socket_,
			boost::asio::buffer(data_, bytes_transferred),
			boost::bind(&Session::handle_write, this,
				boost::asio::placeholders::error));
	}
	else
	{
		delete this;
	}
}


void Session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{

		
	


		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&Session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		delete this;
	}
}
