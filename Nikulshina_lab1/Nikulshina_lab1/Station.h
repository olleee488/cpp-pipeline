#pragma once
#include <string>
#include <fstream>

class Station {
private:
	int id;
	std::string name;
	int workshops;
	int workingWorkshops;
	int stationClass;
	static int nextStationID;
public:
	Station();

	int getId() const { return id; }
	std::string getName() const { return name; }

	double getInactivePercent() const {
		if (workshops == 0) return 0;
		return (double)(workshops - workingWorkshops) / workshops * 100.0;
	}

	void inputStation();
	void printStation() const;
	void startWorkshop();
	void stopWorkshop();
	void saveToFileStation(std::ofstream& file) const;
	void loadFromFileStation(std::ifstream& file);
};