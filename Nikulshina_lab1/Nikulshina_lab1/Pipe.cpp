#include "Pipe.h"
#include <iostream>

int Pipe::nextPipeID = 1;

Pipe::Pipe()
	: id(nextPipeID++), kilometerMark(""), length(0), diameter(0), underRepair(false) {}

Pipe::Pipe(const std::string& km, double len, int diam, bool repair)
	: id(nextPipeID++), kilometerMark(km), length(len), diameter(diam), underRepair(repair) {}

void Pipe::inputPipe() {
	std::cout << "Enter the kilometer mark: ";
	std::getline(std::cin >> std::ws, kilometerMark);

	while (true) {
		std::cout << "Enter length: ";
		if (std::cin >> length && length > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (true) {
		std::cout << "Enter diameter: ";
		if (std::cin >> diameter && diameter > 0 && std::cin.peek() == '\n') break;

		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	underRepair = false;
}

void Pipe::printPipe() const {
	std::cout << "Pipe #" << id << "\n"
		<< "Kilometer marker: " << kilometerMark << "\n"
		<< "Length: " << length << "km\n"
		<< "Diameter: " << diameter << "mm\n"
		<< "Under repair: " << (underRepair ? "Yes" : "No") << "\n\n";
}

void Pipe::toggleRepair() {
	underRepair = !underRepair;
	std::cout << "Pipe #" << id << " repair status changed to: "
		<< (underRepair ? "Yes" : "No") << "\n";
}

void Pipe::saveToFilePipe(std::ofstream& file) const {
	file << id << "\n"
		<< kilometerMark << "\n"
		<< length << "\n"
		<< diameter << "\n"
		<< underRepair << "\n";
}

void Pipe::loadFromFilePipe(std::ifstream& file) {
	file >> id;
	std::getline(file >> std::ws, kilometerMark);
	file >> length >> diameter >> underRepair;
	if (id >= nextPipeID) {
		nextPipeID = id + 1;
	}
}