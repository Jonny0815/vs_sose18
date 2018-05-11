#include "ServerInst.h"



ServerInst::ServerInst(char* port_h)
{

	port = atoi(port_h);

}


ServerInst::~ServerInst()
{
}


void ServerInst::run_udp(boost::asio::io_service& io_service)
{
	

	udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
	for (;;)
	{
		char data[1024];
		udp::endpoint sender_endpoint;
		size_t length = sock.receive_from(
			boost::asio::buffer(data, 1024), sender_endpoint);

		recieved_messurements++;

		string data_s = data;

		string carid_s = data_s.substr(0, 4);
		string id_s = data_s.substr(5, 4);
		string messure_s = data_s.substr(10, 4);
		//string timestamp_s = data_s.substr(15, 20);

		messurements.push_back(messure_s);


		stringstream output;
		output << "Ip: " << sender_endpoint.address() << " CarID: " << carid_s << "\t SensorID: " << id_s<< "\t Value: " << messure_s << "\t Time: "  <<"\n";
		cout << output.str();	


	}

	

}


void ServerInst::write() {

	//ofstream datei;

	fstream datei("save.txt", ios::out);

	datei << messurements.size() << " ";

	copy(messurements.begin(), messurements.end(), ostream_iterator<int>(datei, " "));

	datei.close();

}

void ServerInst::read() {

	ifstream datei;

	datei.open("save.txt", ios::in);

	messurements.clear();

	istream_iterator<int> begin(datei); // Anfangsiterator auf die Datei
	istream_iterator<int> end; // Enditerator
	copy(begin, end, back_inserter(messurements));

	copy(messurements.begin(), messurements.end(), ostream_iterator<int>(cout, " "));

	cout << "Datas read" << endl;
}

