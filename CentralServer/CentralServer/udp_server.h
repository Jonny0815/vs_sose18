#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_server
{
public:
	udp_server(boost::asio::io_service&, short);

	void handle_receive_from(const boost::system::error_code&, size_t);

	void handle_send_to(const boost::system::error_code&, size_t);

private:
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	char data_[max_length];
};