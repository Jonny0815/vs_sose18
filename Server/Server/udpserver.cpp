#include "udpserver.h"



udpserver::udpserver(boost::asio::io_service& io_service, short port): socket_(io_service, udp::endpoint(udp::v4(), port))
{
	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&udpserver::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}



udpserver::~udpserver()
{
}



void udpserver::handle_receive_from(const boost::system::error_code& error,
	size_t bytes_recvd)
{
	if (!error && bytes_recvd > 0)
	{
		socket_.async_send_to(
			boost::asio::buffer(data_, bytes_recvd), sender_endpoint_,
			boost::bind(&udpserver::handle_send_to, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));


		string data_s = data_;

		string carid_s = data_s.substr(0, 4);
		string id_s = data_s.substr(5, 4);
		string messure_s = data_s.substr(10, 4);
		//string timestamp_s = data_s.substr(15, 20);

		messurements.push_back(messure_s);


		stringstream output;
		output << "Ip: " << sender_endpoint_.address() << " CarID: " << carid_s << "\t SensorID: " << id_s << "\t Value: " << messure_s << "\t Time: " << "\n";
		cout << output.str();



	}
	else
	{
		socket_.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
			boost::bind(&udpserver::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
}

void udpserver::handle_send_to(const boost::system::error_code&, size_t)
{
	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&udpserver::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}
