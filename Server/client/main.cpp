#include <iostream>
#include <string>
#include "mqttWrapper.h"



using namespace std;

int main(int argc, char *argv[])
{
	mqttWrapper* mqtt;
	mqtt = new mqttWrapper("test1337", "127.0.0.1", 1883);

	/*std::string value("test123");
	mqtt->myPublish("test", value);
	value = "test321";
	mqtt->myPublish("test", value);*/

	mqtt->subscribe(NULL, "test");

	int rc;


	while (true)
	{

		rc = mqtt->loop();
		if (rc) {
			mqtt->reconnect();
		}

	}




	delete mqtt;

	return 0;
}