#pragma once

#include <string>


class Pet {
private:
	std::string name;
	int age;
	int hunger;
	int happiness;
	int energy;

	void ClampStats();
public:
	Pet(std::string PetName);

	void Feed();
	void Play();
	void Sleep();
	void Update();
	std::string ReadStats(int stat);
	void LoadFromStream(std::istream& in);

	void PrintStats() const;
	bool IsAlive() const;
	std::string data;
	std::string GetData();
};