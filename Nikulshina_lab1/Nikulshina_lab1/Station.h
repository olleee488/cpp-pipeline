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
	Station(const std::string& n, int ws, int aws, int cls);

	int getId() const { return id; }
	std::string getName() const { return name; }
	int getWorkshops() const { return workshops; }
	int getWorkingWorkshops() const { return workingWorkshops; }
	int getStationClass() const { return stationClass; }
	static int getNextID() { return nextStationID; }

	double getInactivePercent() const {
		if (workshops == 0) return 0;
		return (double)(workshops - workingWorkshops) / workshops * 100.0;
	}

	void setName(const std::string& n) { name = n; }
	void setWorkshops(int w) { workshops = w; }
	void setWorkingWorkshops(int w) { workingWorkshops = w; }
	void setStationClass(int c) { stationClass = c; }
	static void setNextID(int val) { nextStationID = val; }

	void inputStation();
	void printStation() const;
	void startWorkshop();
	void stopWorkshop();
	void saveToFileStation(std::ofstream& file) const;
	void loadFromFileStation(std::ifstream& file);
};