#include "Session.h"



Session::Session(boost::asio::io_service& io_service, vector<messurement*>* messurements_h)
	: socket_(io_service)
{
	messurements = messurements_h;
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
		std::cout << data_;

		std::stringstream ss(data_);
		char line[128];

		ss.getline(line,128);

		std::string line_s(line);

		std::string arg(line_s.substr(5, 3));

		std::string http_body;
		std::string http_header;

		stringstream to_send;

		cout << "------------------------" << arg << "--------------------" << endl;

		if (arg == "all")
		{

			

			for (size_t i = 0; i < messurements->size(); i++)
			{
				to_send << messurements->at(i)->get_info();
				cout << "added to_send: " << messurements->at(i)->get_info() << endl;
			}

			http_body = "<html>\r\n<body>\r\n<h1>" + to_send.str();

			http_header = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(http_body.length()) + "\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n";


		}
		else if (all_of(arg.begin(), arg.end(), ::isdigit)) {
			
			bool found = false;

				for (size_t i = 0; i < messurements->size(); i++)
				{
					if (messurements->at(i)->get_carid() == atoi(arg.c_str()))
					{
						found = true;
						to_send << messurements->at(i)->get_info();
					}
				}
			

				if (found)
				{
					http_body = "<html>\r\n<body>\r\n<h1>" + to_send.str() + "";
				}
				else {
					http_body = "<html>\r\n<body>\r\n<h1> no car with id" + arg;
				}
				
				

				http_header = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(http_body.length()) + "\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n";

		}else {


			http_body = "<html>\r\n<body>\r\n<h1> Wrong arguments ";

			http_header = "HTTP/1.1 404 OK\r\nContent-Length: " + std::to_string(http_body.length()) + "\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n";

		}
		
		std::string data_s = http_header + http_body;

		std::cerr << "HTTP Data == " << data_s << std::endl;

		cout << "bytes transfered: " << bytes_transferred << endl;


		cout << "data_s size: " << data_s.length() << endl;

		char data_send[4096];
		strncpy(data_send, data_s.c_str(), 4096);
		
		//cout << "data sended:" << endl << data_send;

		boost::asio::async_write(socket_,
			boost::asio::buffer(data_send, data_s.size()),
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
