#include <iostream>
#include <string>
#include <fstream>

struct Pipe
{
	std::string kilometerMark;
	double length;
	int diameter;
	bool underRepair;
};

struct Station
{
	std::string name;
	int workshops;
	int workingWorkshops;
	int stationClass;
};

void inputPipe(Pipe& pipe) {
	std::cout << "Enter the kilometer mark: ";
	std::getline(std::cin >> std::ws, pipe.kilometerMark);

	while (true) {
		std::cout << "Enter length: ";
		if (std::cin >> pipe.length && pipe.length > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter diameter: ";
		if (std::cin >> pipe.diameter && pipe.diameter > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	pipe.underRepair = false;
}

void printPipe(const Pipe& pipe) {
	std::cout << "Pipe\n"
		<< "Kilometer marker: " << pipe.kilometerMark << "\n"
		<< "Length: " << pipe.length << "km\n"
		<< "Dimeter: " << pipe.diameter << "mm\n"
		<< "Under repair: " << (pipe.underRepair ? "Yes" : "No") << "\n\n";
}

void inputStation(Station& station) {
	std::cout << "Enter station name: ";
	std::getline(std::cin >> std::ws, station.name);

	while (true) {
		std::cout << "Enter the number of workshops: ";
		if (std::cin >> station.workshops && station.workshops > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter the number of active workshops: ";
		if (std::cin >> station.workingWorkshops && station.workingWorkshops >= 0
			&& station.workingWorkshops <= station.workshops && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number. The number of active workshops must be between 0 and "
			<< station.workshops << "\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter station class: ";
		if (std::cin >> station.stationClass && station.stationClass > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
}

void printStation(const Station& station) {
	std::cout << "Station\n" << "Name: " << station.name << "\n"
		<< "The number of workshops: " << station.workshops << "\n"
		<< "The number of active workshops: " << station.workingWorkshops << "\n"
		<< "The station class: " << station.stationClass << "\n\n";
}

void toggleRepair(Pipe& pipe) {
	pipe.underRepair = !pipe.underRepair;
	std::cout << "Pipe repair status changed to: "
		<< (pipe.underRepair ? "Yes" : "No") << "\n";
}

void startWorkshop(Station& station) {
	if (station.workingWorkshops < station.workshops) {
		station.workingWorkshops++;
		std::cout << "Workshop started! Now working: "
			<< station.workingWorkshops << "\n";
	}
	else {
		std::cout << "All workshops are already working!\n";
	}
}

void stopWorkshop(Station& station) {
	if (station.workingWorkshops > 0) {
		station.workingWorkshops--;
		std::cout << "Workshop stopped! Now working: "
			<< station.workingWorkshops << "\n";
	}
	else {
		std::cout << "No working workshops to stop!\n";
	}
}

void showMenu() {
	std::cout << "Control menu\n";
	std::cout << "1. Add a pipe\n";
	std::cout << "2. Add a station\n";
	std::cout << "3. View all objects\n";
	std::cout << "4. Edit a pipe\n";
	std::cout << "5. Edit a station\n";
	std::cout << "6. Save\n";
	std::cout << "7. Load\n";
	std::cout << "0. Exit\n";
	std::cout << "Choose action: ";
}

void saveToFilePipe(const Pipe& pipe, bool hasPipe, std::ofstream& file) {
	file << (hasPipe ? 1 : 0) << "\n";
	if (hasPipe) {
		file << pipe.kilometerMark << "\n"
			<< pipe.length << "\n"
			<< pipe.diameter << "\n"
			<< pipe.underRepair << "\n";
	}
}

void saveToFileStation(const Station& station, bool hasStation, std::ofstream& file) {
	file << (hasStation ? 1 : 0) << "\n";
	if (hasStation) {
		file << station.name << "\n"
			<< station.workshops << "\n"
			<< station.workingWorkshops << "\n"
			<< station.stationClass << "\n";
	}
}

void loadFromFilePipe(Pipe& pipe, bool& hasPipe, std::ifstream& file) {
	int flag;
	file >> flag;
	hasPipe = (flag == 1);
	if (hasPipe) {
		std::getline(file >> std::ws, pipe.kilometerMark);
		file >> pipe.length >> pipe.diameter >> pipe.underRepair;
	}
}

void loadFromFileStation(Station& station, bool& hasStation, std::ifstream& file) {
	int flag;
	file >> flag;
	hasStation = (flag == 1);
	if (hasStation) {
		std::getline(file >> std::ws, station.name);
		file >> station.workshops >> station.workingWorkshops >> station.stationClass;
	}
}

int main() {
	Pipe myPipe;
	Station myStation;
	bool hasPipe = false;
	bool hasStation = false;

	while (true) {
		showMenu();
		int choice;

		if (!(std::cin >> choice)) {
			std::cout << "Error! Please enter a number from 0 to 7\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		switch (choice) {
		case 1:
			inputPipe(myPipe);
			hasPipe = true;
			std::cout << "Pipe added\n";
			break;

		case 2:
			inputStation(myStation);
			hasStation = true;
			std::cout << "Station added\n";
			break;

		case 3:
			std::cout << "\nCurrent objects\n";
			if (hasPipe) {
				printPipe(myPipe);
			}
			else {
				std::cout << "Pipe is no added\n";
			}

			if (hasStation) {
				printStation(myStation);
			}
			else {
				std::cout << "Station is not added\n";
			}
			break;

		case 4:
			if (hasPipe) {
				toggleRepair(myPipe);
			}
			else {
				std::cout << "Error! Pipe is not added yet\n";
			}
			break;

		case 5:
			if (hasStation) {
				std::cout << "\nChoose action for the station\n";
				std::cout << "1. Start a workshop\n";
				std::cout << "2. Stop a workshop\n";
				std::cout << "0. Cancel\n";
				std::cout << "Your choice: ";

				int subChoice;
				if (std::cin >> subChoice) {
					if (subChoice == 1) {
						startWorkshop(myStation);
					}
					else if (subChoice == 2) {
						stopWorkshop(myStation);
					}
					else if (subChoice != 0) {
						std::cout << "Invalid choice\n";
					}
				}
				else {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
			}
			else {
				std::cout << "Error! Station is not added yet\n";
			}
			break;
		case 6:
		{
			std::ofstream file("data.txt");
			if (!file.is_open()) {
				std::cout << "Error! Cannot open file for writing\n";
			}
			else {
				saveToFilePipe(myPipe, hasPipe, file);
				saveToFileStation(myStation, hasStation, file);
				file.close();
			}
		}
		break;
		case 7:
		{
			std::ifstream file("data.txt");
			if (!file.is_open()) {
				std::cout << "Error! Cannot open file for reading\n";
			}
			else {
				loadFromFilePipe(myPipe, hasPipe, file);
				loadFromFileStation(myStation, hasStation, file);
				file.close();
			}
		}
		break;

		case 0:
			std::cout << "Exiting program\n";
			return 0;

		default:
			std::cout << "Error! Enter a valid number\n";
		}
	}
	return 0;
}