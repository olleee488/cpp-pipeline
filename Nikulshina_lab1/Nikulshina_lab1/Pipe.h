#pragma once
#include <string>
#include <fstream>

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

	int getId() const { return id; }
	std::string getKilometerMark() const { return kilometerMark; }
	bool isUnderRepair() const { return underRepair; }

	void inputPipe();
	void printPipe() const;
	void toggleRepair();
	void saveToFilePipe(std::ofstream& file) const;
	void loadFromFilePipe(std::ifstream& file);
};