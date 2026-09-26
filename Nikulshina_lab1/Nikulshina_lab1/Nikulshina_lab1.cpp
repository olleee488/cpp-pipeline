#include <iostream>
#include <string>

struct Pipe
{
	std::string kilometerMark;
	double length;
	int diameter;
	bool underRepair;
};

struct Stantion
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

int main() {
	Pipe myPipe;
	inputPipe(myPipe);
	printPipe(myPipe);
	return 0;
}