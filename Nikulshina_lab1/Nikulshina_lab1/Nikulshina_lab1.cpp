#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "utils.h"

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
std::vector<int> Search(const std::unordered_map<int, TObj>& objs, bool(*filterer)(const TObj&, const T&), const T& x) {
	std::vector<int> subset;
	for (const auto& [id, obj] : objs) {
		if (filterer(obj, x)) {
			subset.push_back(id);
		}
	}
	return subset;
}

Pipe* findPipeById(std::unordered_map<int, Pipe>& pipes, int id) {
	auto it = pipes.find(id);
	if (it != pipes.end()) {
		return &(it->second);
	}
	return nullptr;
}

Station* findStationById(std::unordered_map<int, Station>& stations, int id) {
	auto it = stations.find(id);
	if (it != stations.end()) {
		return &(it->second);
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

std::vector<int> selectSubset(const std::vector<int>& foundIds) {
	std::cout << "Select IDs to process (space-separated, or type 'all'): ";
	std::string input;
	INPUT_LINE(std::cin, input);

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
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;

	logInit("actions.log");

	while (true) {
		showMenu();
		int choice = GetCorrectNumber<int>(0, 12);

		switch (choice) {
		case 1: {
			Pipe p;
			p.inputPipe();
			pipes.insert({ p.getId(), p });
			break;
		}

		case 2: {
			Station s;
			s.inputStation();
			stations.insert({ s.getId(), s });
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
			std::vector<int> found;
			if (sub == 1) {
				std::cout << "Enter name: ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(pipes, filterPipeByName, name);
			} else if (sub == 2) {
				std::cout << "Under repair ? (1/0 or yes/no) : ";
				std::string val;
				INPUT_LINE(std::cin, val);
				found = Search(pipes, filterPipeByRepair, val);
			}
			printIds(found);
			break;
		}

		case 5: {
			std::cout << "Search stations : \n 1. By name \n 2.By inactive % \n Choice : ";
			int sub = GetCorrectNumber<int>(1, 2);
			std::vector<int> found;
			if (sub == 1) {
				std::cout << "Enter name : ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(stations, filterStationByName, name);
			} else if (sub == 2) {
				std::cout << "Min inactive % : ";
				std::string val;
				INPUT_LINE(std::cin, val);
				found = Search(stations, filterStationByInactive, val);
			}
			printIds(found);
			break;
		}

		case 6: {
			std::cout << "Enter pipe ID to edit: ";
			int id = GetCorrectNumber<int>(1, 10000);
			Pipe* p = findPipeById(pipes, id);
			if (!p) {
				std::cout << "Pipe not found\n";

			}
			else {
				p->printPipe();
				p->toggleRepair();
			}
			break;
		}

		case 7: {
			std::cout << "Enter station ID to edit: ";
			int id = GetCorrectNumber<int>(1, 10000);
			Station* s = findStationById(stations, id);
			if (!s) {
				std::cout << "Station not found \n";
			}
			else {
				s->printStation();
				std::cout << "Manage workshops\n";
				std::cout << "1. Start a workshop\n";
				std::cout << "2. Stop a workshop\n";
				std::cout << "0. Cancel\n";
				std::cout << "Your choice: \n";

				int sub = GetCorrectNumber<int>(0, 2);

				if (sub == 1) {
					s->startWorkshop();
				}
				else if (sub == 2) {
					s->stopWorkshop();
				}
				else if (sub != 0) {
					std::cout << "Invalid choice\n";
				}
			}
			break;
		}

		case 8: {
			std::cout << "Batch edit pipes : \n 1. By name \n 2. By repair status \n Choice: ";
			int sub = GetCorrectNumber<int>(1, 2);
			std::vector<int> found;
			if (sub == 1) {
				std::cout << "Enter name : ";
				std::string name;
				INPUT_LINE(std::cin, name);
				found = Search(pipes, filterPipeByName, name);
			}
			else if (sub == 2) {
				std::cout << "Under repair? (0/1): ";
				std::string val;
				INPUT_LINE(std::cin, val);
				found = Search(pipes, filterPipeByRepair, val);
			}
			printIds(found);
			if (found.empty()) break;

			std::vector<int> selected = selectSubset(found);
			std::cout << "Set under repair ? (1/0): ";
			int r = GetCorrectNumber<int>(0, 1);

			for (int id : selected) {
				Pipe* p = findPipeById(pipes, id);
				if (p) {
					if ((r == 1 && !p->isUnderRepair()) || (r == 0 && p->isUnderRepair())) {
						p->toggleRepair();
					}
				}
			}
			std::cout << "Edited " << selected.size() << "pipes \n";
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
					pipes.insert({ p.getId(), p });
				}
				file >> n;
				for (size_t i = 0; i < n; i++) {
					Station s;
					s.loadFromFileStation(file);
					stations.insert({ s.getId(), s });
				}
				file.close();
				std::cout << "Loaded" << pipes.size() << " pipes, " << stations.size() << " stations \n";
			}
			break;
		}

		case 0: {
			logClose();
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