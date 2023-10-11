#include "Passenger.h"

Passenger::Passenger()
	:stopInformation("X"), category('_')
{}

Passenger::Passenger(string stopInfo, char cat)
	:stopInformation(stopInfo), category(cat)
{}

Passenger Passenger::getDefault()
{
	return Passenger();
}

string Passenger::getStopInformation() const
{
	return stopInformation;
}

char Passenger::getCategory() const
{
	return category;
}

void Passenger::trimStopInfo()
{
	this->stopInformation.erase(stopInformation.begin());
	this->stopInformation.erase(stopInformation.begin());

}

bool Passenger::operator==(const Passenger* rhs)
{
	if (this->stopInformation == rhs->stopInformation && this->category == rhs->category)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, Passenger p1)
{
	os << p1.getCategory();
	
	// DEBUGGING PRINT - CHECKING STOP INFO
	// os << p1.getStopInformation();

	return os;
}
