
#include "udp_server.h"



udp_server::udp_server(boost::asio::io_service& io_service, short port): socket_(io_service, udp::endpoint(udp::v4(), port))
{
	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&udp_server::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}



udp_server::~udp_server()
{
}


void udp_server::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
	if (!error && bytes_recvd > 0)
	{
		socket_.async_send_to(
			boost::asio::buffer(data_, bytes_recvd), sender_endpoint_,
			boost::bind(&udp_server::handle_send_to, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		socket_.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
			boost::bind(&udp_server::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
}


void udp_server::handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/)
{
	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&udp_server::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}