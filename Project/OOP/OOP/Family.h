#pragma once
#include "Passenger.h"

class Family : public Passenger
{
	public:
		Family(string stopInfo);
		// bool operator==(Passenger* rhs);
};
