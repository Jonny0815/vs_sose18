//#include <cstdio>
//
//#include <cstdlib>
//#include <iostream>
//#include <boost/bind.hpp>
//#include <boost/asio.hpp>
//#include <boost/thread/thread.hpp>
//#include <vector>
//
//#include "ServerInst.h"
//
//using boost::asio::ip::udp;
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//
//
//	try
//	{
//		if (argc != 2)
//		{
//			std::cerr << "Usage: Server <port> \n";
//			return 1;
//		}
//
//		boost::asio::io_service io_service;
//
//
//
//
//
//		ServerInst s1(argv[1]);
//		s1.run_udp(io_service);
//
//		//boost::thread* thr = new boost::thread(&ServerInst::run_udp, &s1,&io_service); // not working ? neither with c++11 threads
//
//		return 0;
//	}
//
//	catch (std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << "\n";
//	}
//
//
//}




#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session
{
public:
	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

private:
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(data_, bytes_transferred),
				boost::bind(&session::handle_write, this,
					boost::asio::placeholders::error));


			std::cout << "1 "<< std::endl << data_ << std::endl;

		}
		else
		{
			delete this;
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{

			std::string data_s = "HTTP/1.1 200 OK \r\n Date: Thu, 15 Jul 2004 19:20:21 GMT \r\n Server: Apache/1.3.5 (Unix) \r\n Accept-Ranges: bytes \r\n Content-length: 46 \r\n Connection: close \r\n Content-type: text/html \r\n\r\n <h1>Antwort</h1> \r\n <p>Ich bin eine Antwort</p> \r\n";

			char* varchar = new char[data_s.size()];


			strncpy(varchar, data_s.c_str(), data_s.size());

			std::cout << varchar << std::endl;

			socket_.async_read_some(boost::asio::buffer(varchar, data_s.size()),
				boost::bind(&session::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

			std::cout << "sended" << varchar << std::endl;

		}
		else
		{
			delete this;
		}
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

class server
{
public:
	server(boost::asio::io_service& io_service, short port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		session* new_session = new session(io_service_);
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
	}

	void handle_accept(session* new_session,
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

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server s(io_service, atoi(argv[1]));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
