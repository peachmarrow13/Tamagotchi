#include "Utils.h"
#include "Includes.h"
#include "Pet.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstdio>

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
		if (length <= 0)
			length = 30; // Default length if not specified

		if (c == '\0') 
			c = '-'; // Default character if not specified
		
		for (int i = 0; i < length; i++) std::cout << c;
		std::cout << std::endl;
	}
	void Utils::SaveToFile(const std::string& filename, const std::string pet) {
		std::ofstream file(filename, std::ofstream::trunc);
		if (file.is_open()) {
			std::string text = pet;

			file << text;

			file.close();
		}
		else {
			Utils::Exit(1, "Error opening file.\nRun as administrator.\n"); // Exit if the file cannot be opened CODE: 1
		}
	}

	void Utils::Load(Pet& myPet) {
		std::ifstream file("savefile.txt");
		if (!file.is_open()) {
			Utils::Exit(1, "Error opening save file.\nRun as administrator.\n"); // Exit if the file cannot be opened CODE: 1
			std::cin.get();
			return;
		}
		std::cout << "Loading stats from save file...\n";
		myPet.LoadFromStream(file);
		file.close();
	}

	bool Utils::IsSave(const std::string& filename) {
		std::ifstream file(filename);
		std::string text;
		file >> text;
		if (text.empty()) {
			file.close();
			return 0; // Return False if the file is empty
		}
		file.close();
		return 1; // Return True if the file is not empty
	}

	void Utils::TimePassed(Pet& myPet) {
		using std::chrono::system_clock;

		std::ifstream file("Time");
		if (!file.is_open()) {
			Utils::Exit(1, "Error opening time file.\nRun as administrator.\n"); // Exit if the file cannot be opened CODE: 1
			return;
		}

		std::string LastTime;
		file >> LastTime;
		file.close();
		system_clock::time_point Now = system_clock::now();
		system_clock::time_point LastTimePoint = system_clock::from_time_t(std::stoll(LastTime));
		auto duration = std::chrono::duration_cast<std::chrono::hours>(Now - LastTimePoint).count();

		while (duration > 0) {
			myPet.Update();
			auto jo = myPet.ReadStats(2); auto joe = std::stoi(jo); auto joseph = joe + 1;

			myPet.SetStat(2, std::to_string(joseph));
			duration--;
		}
	}

	void Utils::SaveTime(std::string Name) {
		std::ofstream File(Name, std::ofstream::trunc);
		if (File.is_open()) {
			using std::chrono::system_clock;
			system_clock::time_point Now = system_clock::now();

			File << system_clock::to_time_t(Now) << std::endl;

			File.close();
		}
		else {
			Utils::Exit(1, "Error opening time file.\nRun as administrator.\n"); // Exit if the file cannot be opened CODE: 1
		}
	}

	void Utils::Exit(int Code, const std::string& Message) {
		std::cerr << "[FATAL ERROR] " << Message << std::endl;
		std::cout << "Exiting with code: " << Code << std::endl;
		std::cout << "Press Enter to continue..." << std::endl;
		std::cin.ignore(); std::cin.get();
		std::exit(Code);
	}

	/* 
	ERROR CODES:
	1 - File not found or cannot be opened
	
	*/