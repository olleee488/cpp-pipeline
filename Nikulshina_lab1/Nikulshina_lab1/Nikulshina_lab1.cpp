#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <chrono>
#include "Pipe.h"
#include "Station.h"
#include "utils.h"

bool filterPipeByName(const Pipe& p, const std::string& name) {
	return p.getKilometerMark().find(name) != std::string::npos;
}

bool filterPipeByRepair(const Pipe& p, const bool& wantRepair) {
	return p.isUnderRepair() == wantRepair;
}

bool filterStationByName(const Station& s, const std::string& name) {
	return s.getName().find(name) != std::string::npos;
}

bool filterStationByInactive(const Station& s, const double& percent) {
	return s.getInactivePercent() >= percent;
}

template <typename TObj, typename T>
std::set<int> Search(const std::unordered_map<int, TObj>& objs, bool(*filterer)(const TObj&, const T&), const T& x) {
	std::set<int> subset;
	for (const auto& [id, obj] : objs) {
		if (filterer(obj, x)) {
			subset.emplace(id);
		}
	}
	return subset;
}

void printIds(const std::set<int>& ids) {
	if (ids.empty()) {
		std::cout << "Nothing found.\n";
	}
	else {
		std::cout << "Found IDs: ";
		for (int id : ids) std::cout << id << " ";
		std::cout << "\n";
	}
}

std::set<int> selectSubset(const std::set<int>& foundIds) {
	std::cout << "Select IDs to process (1 - All found, 2 - Specific IDs): ";
	int choice = GetCorrectNumber<int>(1, 2);

	if (choice == 1) return foundIds;

	std::set<int> selected;
	std::cout << "Enter ID (0 to finish):\n";
	while (true) {
		int id = GetCorrectNumber<int>(0, 1000000);
		if (id == 0)
			break;
		if (foundIds.count(id)) {
			selected.emplace(id);
		}
		else {
			std::cout << "ID " << id << "not in found set\n";
		}
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
	redirect_output_wrapper cerr_out(std::cerr);
	std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
	std::ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);

	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;

	while (true) {
		showMenu();
		int choice = GetCorrectNumber<int>(0, 12);

		switch (choice) {
		case 1: {
			Pipe p;
			p.inputPipe();
			pipes.emplace( p.getId(), p );
			break;
		}

		case 2: {
			Station s;
			s.inputStation();
			stations.emplace( s.getId(), s );
			break;
		}

		case 3: {
			std::cout << " \n  Pipes : \n ";
			if (pipes.empty()) std::cout << "No pipes. \n";
			for (const auto& [id, p] : pipes) p.printPipe();

			std::cout << " \n  Stations : \n ";
			if (stations.empty()) std::cout << "No stations. \n";
			for (const auto& [id, s] : stations) s.printStation();
			break;
		}

		case 4: {
			std::cout << "Search pipes : \n 1. By name \n 2. By repair status \n Choice :  ";
			int sub = GetCorrectNumber<int>(1, 2);
			std::set<int> found;
			if (sub == 1) {
				std::cout << "Enter name: ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(pipes, filterPipeByName, name);
			} else if (sub == 2) {
				std::cout << "Under repair ? (1/0 or yes/no) : ";
				std::string val;
				INPUT_LINE(std::cin, val);
				bool wantRepair = (val == "1" || val == "yes");
				found = Search(pipes, filterPipeByRepair, wantRepair);
			}
			printIds(found);
			break;
		}

		case 5: {
			std::cout << "Search stations : \n 1. By name \n 2.By inactive % \n Choice : ";
			int sub = GetCorrectNumber<int>(1, 2);
			std::set<int> found;
			if (sub == 1) {
				std::cout << "Enter name : ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(stations, filterStationByName, name);
			} else if (sub == 2) {
				std::cout << "Min inactive % : ";
				double percent = GetCorrectNumber<double>(0.0, 100.0);
				found = Search(stations, filterStationByInactive, percent);
			}
			printIds(found);
			break;
		}

		case 6: {
			std::cout << "Enter pipe ID to edit: ";
			int id = GetCorrectNumber<int>(1, 10000);
			auto it = pipes.find(id);
			if (it != pipes.end()) {
				Pipe& p = it->second;
				p.printPipe();
				p.toggleRepair();
				std::cout << "Pipe update\n";
			}
			else {
				std::cout << "Pipe is not found\n";
			}
			break;
		}

		case 7: {
			std::cout << "Enter station ID to edit: ";
			int id = GetCorrectNumber<int>(1, 10000);
			auto it = stations.find(id);
			if (it != stations.end()) {
				Station& s = it->second;
				s.printStation();
				std::cout << "Manage workshops\n";
				std::cout << "1. Start a workshop\n";
				std::cout << "2. Stop a workshop\n";
				std::cout << "0. Cancel\n";
				std::cout << "Your choice: \n";

				int sub = GetCorrectNumber<int>(0, 2);

				if (sub == 1) {
					s.startWorkshop();
				}
				else if (sub == 2) {
					s.stopWorkshop();
				}
			}
			else {
				std::cout << "Station not found\n";
			}
			break;
		}

		case 8: {
			std::cout << "Batch edit pipes : \n 1. By name \n 2. By repair status \n Choice: ";
			int sub = GetCorrectNumber<int>(1, 2);
			std::set<int> found;
			if (sub == 1) {
				std::cout << "Enter name : ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(pipes, filterPipeByName, name);
			}
			else if (sub == 2) {
				std::cout << "Under repair? (0/1): ";
				bool wantRepair = (GetCorrectNumber<int>(0, 1) == 1);
				found = Search(pipes, filterPipeByRepair, wantRepair);
			}
			printIds(found);
			if (found.empty()) break;

			std::set<int> selected = selectSubset(found);
			if (selected.empty()) break;

			std::cout << "Action:\n 1. Set repair status\n 2. Delete pipes\n Choice: ";
			int action = GetCorrectNumber<int>(1, 2);

			if (action == 1) {
				std::cout << "Set under repair ? (1/0): ";
				int r = GetCorrectNumber<int>(0, 1);
				for (int id : selected) {
					auto it = pipes.find(id);
					if (it != pipes.end()) {
						Pipe& p = it->second;
						if ((r == 1 && !p.isUnderRepair()) || (r == 0 && p.isUnderRepair())) {
							p.toggleRepair();
						}
					}
				}
				std::cout << "Edited " << selected.size() << " pipes\n";
			}
			else if (action == 2) {
				for (int id : selected) {
					pipes.erase(id);
				}
				std::cout << "Deleted " << selected.size() << " pipes\n";
			}
			break;
		}

		case 9 : {
			std::cout << "Enter pipe ID to delete: ";
			int id = GetCorrectNumber<int>(1, 10000);
			if (pipes.erase(id) > 0) {
				std::cout << "Pipe deleted\n";
			}
			else {
				std::cout << "Pipe not found";
			}
			break;
		}

		case 10: {
			std::cout << "Enter station ID to delete: ";
			int id = GetCorrectNumber<int>(1, 10000);
			if (stations.erase(id) > 0) {
				std::cout << "Station deleted \n";
			}
			else {
				std::cout << "Station not found\n ";
			}
			break;
		}

		case 11: {
			std::cout << "Enter filename to save : ";
			std::string filename;
			INPUT_LINE(std::cin, filename);
			std::ofstream file(filename);

			if (!file.is_open()) {
				std::cout << "Error: Failed to open file\n";
			}
			else {
				file << pipes.size() << "\n";
				for (const auto& [id, p] : pipes) p.saveToFilePipe(file);
				file << stations.size() << "\n";
				for (const auto& [id, s] : stations) s.saveToFileStation(file);
				file.close();
				std::cout << "Saved \n";
			}
			break;
		}

		case 12: {
			std::cout << "Enter filename to load : ";
			std::string filename;
			INPUT_LINE(std::cin, filename);
			std::ifstream file(filename);
			if (!file.is_open()) {
				std::cout << "Failed to open file\n";
			}
			else {
				pipes.clear();
				stations.clear();
				size_t n;
				file >> n;
				for (size_t i = 0; i < n; i++) {
					Pipe p;
					p.loadFromFilePipe(file);
					pipes.emplace( p.getId(), p );
				}
				file >> n;
				for (size_t i = 0; i < n; i++) {
					Station s;
					s.loadFromFileStation(file);
					stations.emplace( s.getId(), s );
				}
				file.close();
				std::cout << "Loaded" << pipes.size() << " pipes, " << stations.size() << " stations \n";
			}
			break;
		}

		case 0: {
			std::cout << " Exiting program \n";
			return 0;
		}
		default: {
			std::cout << "Error. Enter a valid number\n";
		}
	}
	}
	return 0;
}