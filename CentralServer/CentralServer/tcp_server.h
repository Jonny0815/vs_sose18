

#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "session.h"

using boost::asio::ip::tcp;


class tcp_server
{
public:
	tcp_server(boost::asio::io_service&, short);

private:
	void start_accept();

	void handle_accept(session*, const boost::system::error_code&);


	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;

};

