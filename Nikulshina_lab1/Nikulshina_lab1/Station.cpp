#include "Station.h"
#include "utils.h"
#include <iostream>

int Station::nextStationID = 1;

Station::Station()
	:id(nextStationID++), name(""), workshops(0), workingWorkshops(0), stationClass(0) {}

void Station::inputStation() {
	std::cout << "Enter station name: ";
	std::string n;
	INPUT_LINE(std::cin, n);
	name = n;

	std::cout << "Enter the number of workshops: ";
	workshops = GetCorrectNumber<int>(1, 100);
	
	std::cout << "Enter the number of active workshops: ";
	workingWorkshops = GetCorrectNumber<int>(1, workshops);

	std::cout << "Enter station class: ";
	stationClass = GetCorrectNumber<int>(1, 5);
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