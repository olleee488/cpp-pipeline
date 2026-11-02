#include "Pipe.h"
#include "utils.h"
#include <iostream>

int Pipe::nextPipeID = 1;

Pipe::Pipe()
	: id(nextPipeID++), kilometerMark(""), length(0), diameter(0), underRepair(false) {}

void Pipe::inputPipe() {
	std::cout << "Enter the kilometer mark: ";
	std::string km;
	INPUT_LINE(std::cin, km);
	kilometerMark = km;

	std::cout << "Enter length: ";
	length = GetCorrectNumber<double>(0.1, 10000.0);

	std::cout << "Enter diameter: ";
	diameter = GetCorrectNumber<int>(10, 5000);

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