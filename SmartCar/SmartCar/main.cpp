#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <thread>

#include "Car.h"
#include "Sensor.h"


using namespace std;

int main(int argc, char *argv[])
{

	if (argc != 1) {
		cerr << "Usage: " << argv[0]
			<< "number_of_cars" << endl;
		return(1);
	}

	int numCars = atoi(argv[1]);

	vector<Car*> cars;
	vector<thread*> threads;

	for (size_t i = 0; i < numCars; i++)
	{
		cars.push_back(new Car);
	}



    return 0;
}