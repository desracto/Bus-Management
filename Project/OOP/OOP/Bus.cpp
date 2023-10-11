#include "Bus.h"

Bus::Bus()
{
	seatingPlan =
	{
		{Passenger("X", 'D'), Passenger("X", 'O'), Passenger("X", 'O'), Passenger("X", 'R')},

		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},

		{Passenger("X", 'D'), Passenger("X", 'O'), Passenger("X", 'O'), Passenger("X", 'R')},

		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},
		{Passenger(), Passenger(), Passenger(), Passenger()},

		{Passenger("X", 'D'), Passenger("X", 'O'), Passenger("X", 'O'), Passenger("X", 'R')},

	};

}
ostream& operator<<(ostream& os, const Bus b1)
{
	for (int row = 0; row < b1.seatingPlan.size(); row++)
	{
		if (row == 0 || row == 5 || row == 10)
		{
			os << "                      DOOR" << endl;
			continue;
		}

		for (int col = 0; col < b1.seatingPlan[row].size(); col++)
		{
			os << "  " << b1.seatingPlan[row][col] << "   ";
		}

		cout << endl;
		cout << endl;

	}

	return os;
}

// NON-CLASS FUNCTIONS
int retrieveCurrentFamilyID()
{
	fstream retrieveID("FamilyIdentifiers.txt", std::ios::in);
	
	int ID;
	retrieveID >> ID;
	ID++;

	retrieveID.close();
	fstream storeID("FamilyIdentifiers.txt", std::ios::out);
	storeID << ID;
	storeID.close();

	return ID;
}
vector<Passenger> constructFamily(Passenger* p1)
{
	vector<Passenger> Family;

	bool MotherCreated = false;
	int familyID = retrieveCurrentFamilyID();

	for (int i = 0; i < 3; i++)
	{
		string stopInfo = (*p1).getStopInformation();
		stopInfo.push_back('F');
		stopInfo.append(std::to_string(familyID));
		
		// cout << stopInfo << " ";

		if (!MotherCreated)
		{
			Lady L_Family(stopInfo);
			Family.push_back(L_Family);
			MotherCreated = true;
		}
		else
		{
			Child C_Family(stopInfo);
			Family.push_back(C_Family);
		}
	}

	return Family;
}
vector<Passenger> retrievePassengers(const char stop)
{
	vector<Passenger> PassengerList;

	string filename = "Passengers.txt";
	fstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		cout << "  ERROR IN OPENING FILE!";
		return PassengerList;
	}

	string line;
	while (getline(file, line))
	{
		// SKIPPING COMMENTS AND OUT-OF-STOP-SCOPE STOPS
		if (line[0] != stop)
		{
			continue;
		}

		int delim_find = line.find(' ');
		
		string stopInfo = line.substr(0, delim_find);
		char category = line.substr(delim_find + 1, line.size())[0];

		if (category == 'L')
		{
			PassengerList.push_back(Lady(stopInfo));
		}
		else if (category == 'M')
		{
			PassengerList.push_back(Men(stopInfo));
		}
		else if (category == 'C')
		{
			PassengerList.push_back(Child(stopInfo));
		}
		else if (category == 'F')
		{
			PassengerList.push_back(Family(stopInfo));
		}
		else if (category == 'T')
		{
			PassengerList.push_back(Passenger(stopInfo, 'T'));
		}
	}
	file.close();
	return PassengerList;
}
void resetFamilyIdentifiers()
{
	fstream file("FamilyIdentifiers.txt", std::ios::out);
	file << 0;
	file.close();
}
bool removeFamily(Bus& b1, Passenger* p1)
{
	bool firstFamilyMatch = false;
	int firstFamilyMatchIndex;
	string stopInfo = (*p1).getStopInformation();
	
	RESTART_LABEL:
	for (size_t r = 0; r < b1.seatingPlan.size(); r++)
	{
		for (size_t c = 0; c < b1.seatingPlan[r].size(); c++)
		{
			if (!firstFamilyMatch)
			{
				string info = b1.seatingPlan[r][c].getStopInformation();

				if (info.size() > 2)
				{
					// cout << "test 1";
					int firstFamilyMatchIndex = b1.seatingPlan[r][c].getStopInformation()[2] - '0';

					stopInfo.push_back('F');
					stopInfo.append(std::to_string(firstFamilyMatchIndex));

					firstFamilyMatch = true;

					goto RESTART_LABEL;
				}
			}
			if (firstFamilyMatch)
			{
				if (b1.seatingPlan[r][c].getStopInformation() == stopInfo)
				{
					b1.seatingPlan[r][c] = Passenger::getDefault();
				}
			}
		}
	}
	
	return true;
}
// END

bool addPassengerToBus(Bus& b1, Passenger* p1)
{
	bool seatedBoolFlag = false;
	const Passenger* DEFAULT_PASSENGER_CONTAINER = new Passenger();

	// DEFAULT LIMITERS
	// Change if passenger being seated have special conditions
	int rowStart = 0;
	int rowLimit = 11;

	int colStart = 0;
	int colLimit = 4;

	if ((*p1).getCategory() == 'L')
	{}
	else if ((*p1).getCategory() == 'M' || (*p1).getCategory() == 'T')
	{
		rowStart = 6;
	}
	else if ((*p1).getCategory() == 'C')
	{
		colLimit = 2;
	}
	else if ((*p1).getCategory() == 'F')
	{
		vector<Passenger> family = constructFamily(p1);

		for (size_t i = 0; i < family.size(); i++)
		{
			addPassengerToBus(b1, &family[i]);
		}

		return true;
	}

	for (int row = rowStart; row < rowLimit; row++)
	{
		if (row == 0 || row == 5 || row == 10) continue;

		for (int col = colStart; col < colLimit; col++)
		{
			if (b1.seatingPlan[row][col] == DEFAULT_PASSENGER_CONTAINER)
			{
				b1.seatingPlan[row][col] = (*p1);
				return true;
			}
		}
	}

	return false;
}
bool removePassengerFromBus(Bus& b1, Passenger* p1)
{
	if ((*p1).getCategory() == 'F')
	{
		removeFamily(b1, p1);
		return true;
	}

	for (size_t row = 0; row < b1.seatingPlan.size(); row++)
	{
		for (size_t col = 0; col < b1.seatingPlan[row].size(); col++)
		{
			if (b1.seatingPlan[row][col] == p1)
			{
				b1.seatingPlan[row][col] = Passenger::getDefault();
				return true;
			}
		}
	}

	return false;
}

void processNextStop(Bus& b1, const char stop)
{
	vector<Passenger> _list = retrievePassengers(stop);

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getStopInformation()[1] == 'A')
		{
			_list[i].trimStopInfo();
			addPassengerToBus(b1, &_list[i]);
		}
		else if (_list[i].getStopInformation()[1] == 'R')
		{
			_list[i].trimStopInfo();
			removePassengerFromBus(b1, &_list[i]);
		}
	}

	b1.savePlanToFile(stop);
}

void resetBus(Bus& b1, char& stop)
{
	for (size_t r = 0; r < b1.seatingPlan.size(); r++)
	{
		for (size_t c = 0; c < b1.seatingPlan[r].size(); c++)
		{
			b1.seatingPlan[r][c] = Passenger::getDefault();
		}
	}

	stop = '@';
	resetFamilyIdentifiers();
}

void Bus::savePlanToFile(const char& stop)
{
	string fileName = "savedstops/Saved_Stop.txt";
	fileName.insert(21, 1, stop);
	fstream file(fileName, std::ios::out);

	for (int r = 0; r < seatingPlan.size(); r++)
	{
		for (int c = 0; c < seatingPlan[r].size(); c++)
		{
			file << seatingPlan[r][c].getStopInformation() << "|" << seatingPlan[r][c].getCategory() << ",";
		}

		file << endl;
	}
}