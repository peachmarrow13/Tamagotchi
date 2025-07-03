#include <random>
#include <chrono>
#include <thread>
#include <iostream>
#include "Utils.h"


int Utils::getRandomNumber(int min, int max) {
	static std::random_device rd;  // Seed
	static std::mt19937 gen(rd()); // Mersenne Twister engine, whatever tf that is.
	std::uniform_int_distribution<> distr(min, max);
	return distr(gen);
}
	int Utils::Clamp(int value, int min, int max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
	void Utils::delay(unsigned int milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
	void Utils::clearScreen() {
		#ifdef _WIN32
		system("cls");
		#else
		system("clear");
		#endif
	}
	void Utils::printSeparator(char c, int length) {
		for (int i = 0; i < length; i++) std::cout << c;
		std::cout << std::endl;
	}
