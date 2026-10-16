#pragma once
#include <stdlib.h>
#include <string>

class Station {
private:
	std::string name;
	int workshops;
	int workingWorkshops;
	int stationClass;
public:
	void inputStation(Station& station);
	void inputStation(Station& station);
	void startWorkshop(Station& station);
	void stopWorkshop(Station& station);
	void saveToFileStation(const Station& station, bool hasStation, std::ofstream& file);
	void loadFromFileStation(Station& station, bool& hasStation, std::ifstream& file);
};