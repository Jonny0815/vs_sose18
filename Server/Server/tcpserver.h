#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "Session.h"


class tcpserver
{
public:
	tcpserver(boost::asio::io_service&,short);
	~tcpserver();


private:

	void start_accept();
	void handle_accept(Session*,const boost::system::error_code&);

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;

};

