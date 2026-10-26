#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
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
using StationFilter = bool(*)(const Station& s, const std::string& x);

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

std::string getInputString(const std::string& prompt) {
	std::cout << prompt;
	std::string ret;
	std::getline(std::cin >> std::ws, ret);
	return ret;
}

int getInt(const std::string& prompt) {
	int val;
	while (true) {
		std::cout << prompt;
		if (std::cin >> val && std::cin.peek() == '\n') break;
		std::cout << "Error! Enter a valid number\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	return val;
}

std::vector<int> selectSubset(const std::vector<int>& foundIds) {
	std::cout << "Select IDs to process (space-separated, or type 'all'): ";
	std::string input;
	std::getline(std::cin >> std::ws, input);

	if (input == "all") return foundIds;

	std::vector<int> selected;
	std::istringstream iss(input);
	int id;
	while (iss >> id) {
		bool exists = false;
		for (int fid : foundIds) {
			if (fid == id) { exists = true; break; }
		}
		if (exists) selected.push_back(id);
		else std::cout << "ID" << id << "not in found set, skipped.\n";
	}
	return selected;
}

void showMenu() {
	std::cout << "Control menu\n";
	std::cout << "1. Add a pipe\n";
	std::cout << "2. Add a station\n";
	std::cout << "3. View all objects\n";
	std::cout << "4. Search pipes\n";
	std::cout << "5. Search stations\n";
	std::cout << "6. Edit a pipe\n";
	std::cout << "7. Edit a station\n";
	std::cout << "8. Batch edit pipes\n";
	std::cout << "9. Delete a pipe\n";
	std::cout << "10. Delete a station\n";
	std::cout << "11. Save to file\n";
	std::cout << "12. Load from file\n";
	std::cout << "0. Exit\n";
	std::cout << "Choose action: ";
}

int main() {
	logInit("actions.log");
	logMessage("Program started");
	Pipe p;
	p.inputPipe();
	p.printPipe();
	logMessage("Test pipe created");

	logMessage("Program exited");
	logClose();
	return 0;
}