#include "Station.h"
#include <iostream>

int Station::nextStationID = 1;

Station::Station()
	:id(nextStationID++), name(""), workshops(0), workingWorkshops(0), stationClass(0) {}

Station::Station(const std::string& n, int ws, int aws, int cls)
	:id(nextStationID++), name(n), workshops(ws), workingWorkshops(aws), stationClass(cls) {}

void Station::inputStation() {
	std::cout << "Enter station name: ";
	std::getline(std::cin >> std::ws, name);

	while (true) {
		std::cout << "Enter the number of workshops: ";
		if (std::cin >> workshops && workshops > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter the number of active workshops: ";
		if (std::cin >> workingWorkshops && workingWorkshops >= 0
			&& workingWorkshops <= workshops && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number. The number of active workshops must be between 0 and "
			<< workshops << "\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter station class: ";
		if (std::cin >> stationClass && stationClass > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
}

void Station::printStation() const {
	std::cout << "Station #" << id << "\n"
		<< "Name: " << name << "\n"
		<< "The number of workshops: " << workshops << "\n"
		<< "The number of active workshops: " << workingWorkshops << "\n"
		<< "The station class: " << stationClass << "\n\n";
}

void Station::startWorkshop() {
	if (workingWorkshops < workshops) {
		workingWorkshops++;
		std::cout << "Workshop started! Now working: "
			<< workingWorkshops << "\n";
	}
	else {
		std::cout << "All workshops are already working!\n";
	}
}

void Station::stopWorkshop() {
	if (workingWorkshops > 0) {
		workingWorkshops--;
		std::cout << "Workshop stopped! Now working: "
			<< workingWorkshops << "\n";
	}
	else {
		std::cout << "No working workshops to stop!\n";
	}
}

void Station::saveToFileStation(std::ofstream& file) const {
	file << id << "\n"
		<< name << "\n"
		<< workshops << "\n"
		<< workingWorkshops << "\n"
		<< stationClass << "\n";
}

void Station::loadFromFileStation(std::ifstream& file) {
	file >> id;
	std::getline(file >> std::ws, name);
	file >> workshops >> workingWorkshops >> stationClass;

	if (id >= nextStationID) {
		nextStationID = id + 1;
	}
}