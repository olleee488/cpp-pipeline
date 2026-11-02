#pragma once
#include <iostream>
#include <string>
#include <fstream>

static std::ofstream g_logFile;

inline void logInit(const std::string& filename) {
	g_logFile.open(filename, std::ios::app);
}

inline void logClose() {
	if (g_logFile.is_open()) {
		g_logFile.close();
	}
}

inline void logInput(const std::string& value) {
	if (g_logFile.is_open()) {
		g_logFile << value << "\n";
		g_logFile.flush();
	}
	std::cout << value << "\n";
}

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						logInput(str)

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()
		|| std::cin.peek() != '\n'
		|| x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type number (" << min << "-" << max << "):";
	}
	logInput(std::to_string(x));
	return x;
}