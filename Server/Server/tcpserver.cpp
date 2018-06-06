#include "tcpserver.h"



tcpserver::tcpserver(boost::asio::io_service& io_service, short port, std::vector<messurement*>* messurements_h)
	: io_service_(io_service),
	acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
{

	messurements = messurements_h;

	start_accept();
}



tcpserver::~tcpserver()
{
}



void tcpserver::start_accept()
{
	Session* new_session = new Session(io_service_, messurements);
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&tcpserver::handle_accept, this, new_session,
			boost::asio::placeholders::error));
}

void tcpserver::handle_accept(Session* new_session,
	const boost::system::error_code& error)
{
	if (!error)
	{
		new_session->start();
	}
	else
	{
		delete new_session;
	}

	start_accept();
}

