#include "Pipe.h"
#include <iostream>
#include <fstream>

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

void Pipe::printPipe() {
	std::cout << "Pipe\n"
		<< "Kilometer marker: " << kilometerMark << "\n"
		<< "Length: " << length << "km\n"
		<< "Dimeter: " << diameter << "mm\n"
		<< "Under repair: " << (underRepair ? "Yes" : "No") << "\n\n";
}

void Pipe::toggleRepair() {
	underRepair = !underRepair;
	std::cout << "Pipe repair status changed to: "
		<< (underRepair ? "Yes" : "No") << "\n";
}

void Pipe::saveToFilePipe(std::ofstream& file) {
	file << kilometerMark << "\n"
		<< length << "\n"
		<< diameter << "\n"
		<< underRepair << "\n";
}

void Pipe::loadFromFilePipe(std::ifstream& file) {
	int flag;
	file >> flag;
	std::getline(file >> std::ws, kilometerMark);
	file >> length >> diameter >> underRepair;
}