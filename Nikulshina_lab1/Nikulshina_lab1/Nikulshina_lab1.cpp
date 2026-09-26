#include <iostream>
#include <string>

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
		if (std::cin >> pipe.length && pipe.length > 0) break;

		std::cout << "Error! Length must be greater than 0\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter diameter: ";
		if (std::cin >> pipe.diameter && pipe.diameter > 0) break;

		std::cout << "Error! Diameter must be greater than 0\n";
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
		if (std::cin >> station.workshops && station.workshops > 0) break;

		std::cout << "Error! The number of workshops must be greater than 0\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter the number of active workshops: ";
		if (std::cin >> station.workingWorkshops && station.workingWorkshops >= 0
			&& station.workingWorkshops <= station.workshops) break;

		std::cout << "Error! The number of active workshops must be between 0 and "
			<< station.workshops << "\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter station class: ";
		if (std::cin >> station.stationClass && station.stationClass > 0) break;

		std::cout << "Error! Station class must be greater than 0\n";
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

int main() {
	Pipe myPipe;
	inputPipe(myPipe);
	printPipe(myPipe);
	Station myStation;
	inputStation(myStation);
	printStation(myStation);
	return 0;
}