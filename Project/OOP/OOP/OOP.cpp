#include <iostream>
#include <vector>
#include "All_Passenger_Classes.h"
#include "Bus.h"

using std::cin;

void startProgram(Bus& B1);
void startAdminMode();
void retrievePlan(const char& choice);


int main()
{
	Bus b1;
	startProgram(b1);
}

void startProgram(Bus& B1)
{
	// CONSTANT DECLARAITIONS
	const char NEXT_STOP = 'd';
	const char RESET = 'r';
	const char QUIT = 'q';
	const char ADMIN_MODE = 'a';

	// GLOBAL VARIABLES
	char stop = '@';

	cout << "Welcome!";

	bool flag = false;
	while (!flag)
	{
		cout << "Stop: " << stop << endl;
		cout << B1;

		cout << "\nPress D to go to the next stop" << endl;
		cout << "Press R to reset" << endl;
		cout << "Press Q to quit" << endl;
		cout << "Press A to enter Administrator mode" << endl;
		cout << "Choice: " << endl;

		char UserInput;
		cin >> UserInput;

		switch (tolower(UserInput))
		{
			case NEXT_STOP:
			{
				if (stop >= 'F')
				{
					cout << "  You have reached the final stop. ";
					cout << "  Please reset the plan or insert a new set of passenegers.";
					break;
				}

				stop++;
				processNextStop(B1, stop);
				break;
			}
			case RESET:
			{
				resetBus(B1, stop);
				break;
			}
			case QUIT:
			{
				resetBus(B1, stop);
				std::cout << "Quitting program.." << std::endl;
				flag = true;
				break;
			}
			case ADMIN_MODE:
			{
				startAdminMode();
				break;
			}
			default:
			{
				cout << "  Invalid Choice!";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

		}

	}
}

void startAdminMode()
{
	bool returnState = false;

	// CONSTANTS
	const char CASE_QUIT_STATE = 'q';
	const char STOP_A = 'a';
	const char STOP_B = 'b';
	const char STOP_C = 'c';
	const char STOP_D = 'd';
	const char STOP_E = 'e';

	while (!returnState)
	{
		cout << "\n\n  ADMIN MODE\n\n";
		cout << "  Which stop would you like to retrieve?\n";
		cout << "  Press Q to exit Admin Mode\n";
		cout << "  Stop: A/B/C/D/E\n";
		cout << "  Choice: ";

		char choice;
		cin >> choice;

		switch (tolower(choice))
		{
			case CASE_QUIT_STATE:
			{
				returnState = true;
				break;
			}
			case STOP_A:
			case STOP_B:
			case STOP_C:
			case STOP_D:
			case STOP_E:
			{
				retrievePlan(choice);
				break;
			}
			default:
			{
				cout << "  Invalid Choice!";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

	}
}

void retrievePlan(const char& choice)
{
	string fileName = "savedstops/Saved_Stop.txt";
	fileName.insert(21, 1, choice);
	fstream file(fileName, std::ios::in);

	if (!file.is_open())
	{
		cout << "\n\n  The simulated stop " << choice << " has not been saved yet.Please run the simulation and save it.";
		return;
	}

	string file_line;
	// Getting each row from the file
	// Each row in the file is a row in the bus
	while (getline(file, file_line))
	{
		stringstream ss(file_line);
		string split;

		while (getline(ss, split, ','))
		{
			string passengerInformation = split.substr(0, split.find('|'));
			char passenger = split.substr(split.find('|') + 1, split.size())[0];

			if (passenger == 'D')
			{
				cout << "                      DOOR" << endl;
				continue;
			}
			if (passenger == 'O' || passenger == 'R') continue;

			cout << "       " << passenger;
		}

		cout << endl;
		cout << endl;
	}
}