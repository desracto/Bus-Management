#pragma once
#include <vector> // USING : vector
#include <iostream> // USING : ostream, cout, endl 
#include <fstream> // USING : fstream
#include <sstream> // USING : stringstream
#include <unordered_map> // USING : unordered_map

#include "All_Passenger_Classes.h"

using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::fstream;
using std::stringstream;
using std::unordered_map;

class Bus
{
	private:
		vector<vector<Passenger>> seatingPlan;
	
	public:
		Bus();
		friend ostream& operator<< (ostream& os, const Bus b1);

		friend void processNextStop(Bus& b1, const char stop);

		friend bool addPassengerToBus(Bus& b1, Passenger* p1);
		friend bool removePassengerFromBus(Bus& b1, Passenger* p1);
		friend bool removeFamily(Bus& b1, Passenger* p1);

		friend void resetBus(Bus& b1, char& stop);
		void savePlanToFile(const char& stop);

		
};
