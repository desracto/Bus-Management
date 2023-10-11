#pragma once
#include <string>
#include <iostream>

using std::ostream;
using std::string;

class Passenger
{
	private:
		string stopInformation;
		char category;

	public:
		Passenger();
		Passenger(string stopInformation, char cat);
		static Passenger getDefault();

		string getStopInformation() const;
		char getCategory() const;

		void trimStopInfo();

		virtual bool operator==(const Passenger* rhs); 
		friend ostream& operator<< (ostream& os, Passenger p1);

};
