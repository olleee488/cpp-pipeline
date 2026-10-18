#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Pipe.h"
#include "Station.h"

std::ofstream logFile;

void logInit(const std::string & filename) {
	logFile.open(filename, std::ios::app);
}

void logMessage(const std::string& msg) {
	if (logFile.is_open()) {
		logFile << msg << "\n";
		logFile.flush();
	}
	std::cout << "[LOG]" << msg << "\n";
}

void logClose() {
	if (logFile.is_open()) {
		logFile.close();
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

int main() {
	logInit("actions.log");
	logMessage("Program started");
	Pipe p;
	p.inputPipe();
	p.printPipe();
	logMessage("Test pipe creatad");

	logMessage("Program exited");
	logClose();
	return 0;
}