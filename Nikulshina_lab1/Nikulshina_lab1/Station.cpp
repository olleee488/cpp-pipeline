#include "Station.h"
#include <iostream>
#include <fstream>

void Station::inputStation(Station& station) {
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

void Station::inputStation(Station& station) {
	std::cout << "Station\n" << "Name: " << station.name << "\n"
		<< "The number of workshops: " << station.workshops << "\n"
		<< "The number of active workshops: " << station.workingWorkshops << "\n"
		<< "The station class: " << station.stationClass << "\n\n";
}

void Station::startWorkshop(Station& station) {
	if (station.workingWorkshops < station.workshops) {
		station.workingWorkshops++;
		std::cout << "Workshop started! Now working: "
			<< station.workingWorkshops << "\n";
	}
	else {
		std::cout << "All workshops are already working!\n";
	}
}

void Station::stopWorkshop(Station& station) {
	if (station.workingWorkshops > 0) {
		station.workingWorkshops--;
		std::cout << "Workshop stopped! Now working: "
			<< station.workingWorkshops << "\n";
	}
	else {
		std::cout << "No working workshops to stop!\n";
	}
}

void Station::saveToFileStation(const Station& station, bool hasStation, std::ofstream& file) {
	file << (hasStation ? 1 : 0) << "\n";
	if (hasStation) {
		file << station.name << "\n"
			<< station.workshops << "\n"
			<< station.workingWorkshops << "\n"
			<< station.stationClass << "\n";
	}
}

void Station::loadFromFileStation(Station& station, bool& hasStation, std::ifstream& file) {
	int flag;
	file >> flag;
	hasStation = (flag == 1);
	if (hasStation) {
		std::getline(file >> std::ws, station.name);
		file >> station.workshops >> station.workingWorkshops >> station.stationClass;
	}
}

