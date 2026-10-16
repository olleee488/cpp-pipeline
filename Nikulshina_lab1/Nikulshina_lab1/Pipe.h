#pragma once
#include <stdlib.h>
#include <string>

class Pipe {
private:
	int id;
	std::string kilometerMark;
	double length;
	int diameter;
	bool underRepair;
	static int nextPipeID;
public:
	Pipe();
	Pipe(const std::string& km, double len, int diam, bool repair);

	int detId() const { return id; }
	std::string getKilometerMark() const { return kilometerMark; }
	double getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool isUnderRepair() const { return underRepair; }
	static int getNextID() { return nextPipeID; }

	void setKilometerMark(const std::string& km) { kilometerMark = km; }
	void setLength(double len) { length = len; }
	void setDiameter(int diam) { diameter = diam; }
	void toggleRepair() { underRepair = !underRepair; }
	static void setNextID(int val) { nextPipeID = val; }

	void inputPipe();
	void printPipe();
	void toggleRepair();
	void saveToFilePipe(std::ofstream& file);
	void loadFromFilePipe(std::ifstream& file);
};