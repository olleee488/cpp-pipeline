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

using PipeFilter = bool(*)(const Pipe& p, const std::string& x);
using StationFilte = bool(*)(const Station& s, const std::string& x);

bool filterPipeByName(const Pipe& p, const std::string& name) {
	return p.getKilometerMark() == name;
}

bool filterPipeByRepair(const Pipe& p, const std::string& x) {
	bool wantRepair = (x == "1" || x == "yes");
	return p.isUnderRepair() == wantRepair;
}

bool filterStationByName(const Station& s, const std::string& name) {
	return s.getName() == name;
}

bool filterStationByInactive(const Station& s, const std::string& x) {
	double percent = std::stod(x);
	return s.getInactivePercent() >= percent;
}

template <typename TObj, typename T>
std::vector<int> Search(const std::vector<TObj>& objs, bool(*filterer)(const TObj&, T), T x) {
	std::vector<int> subset;
	for (const auto& o : objs) {
		if (filterer(o, x)) {
			subset.push_back(o.getId());
		}
	}
	return subset;
}

Pipe* findPipeById(std::vector<Pipe>& pipes, int id) {
	for (auto& p : pipes) {
		if (p.getId() == id) return &p;
	}
	return nullptr;
}

Station* findStationById(std::vector<Station>& stations, int id) {
	for (auto& s : stations) {
		if (s.getId() == id) return &s;
	}
	return nullptr;
}

void printIds(const std::vector<int>& ids) {
	if (ids.empty()) {
		std::cout << "Nothing found.\n";
	}
	else {
		std::cout << "Found IDs: ";
		for (int id : ids) std::cout << id << " ";
		std::cout << "\n";
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