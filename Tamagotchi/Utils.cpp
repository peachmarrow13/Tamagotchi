#include "Utils.h"
#include "Includes.h"
#include "Pet.h"
#include <ctime>
#include <ratio>
#include <chrono>

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
	void Utils::SaveToFile(const std::string& filename, const std::string pet) {
		std::ofstream file(filename, std::ofstream::trunc);
		if (file.is_open()) {
			std::string text = pet;

			file << text;

			file.close();
		}
		else {
			std::cerr << "Error opening file: " << filename << std::endl;
		}
		std::ofstream File("Time", std::ofstream::trunc);
		if (File.is_open()) {
			using std::chrono::system_clock;
			system_clock::time_point Now = system_clock::now();
		
			File << system_clock::to_time_t(Now) << std::endl;

			File.close();
		}
		else {
			std::cerr << "Error opening time file.\n";
		}
	}

	void Utils::Load(Pet& myPet) {
		std::ifstream file("savefile.txt");
		if (!file.is_open()) {
			std::cerr << "Error opening save file.\n";
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
		if (text.empty())
			return 0;
		else
			return 1;
	}

	void Utils::TimePassed(Pet& myPet) {
		using std::chrono::system_clock;

		std::ifstream file("Time");
		if (!file.is_open()) {
			std::cerr << "Error opening time file.\n";
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
			duration--;
		}
	}