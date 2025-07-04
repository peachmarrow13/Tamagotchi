#pragma once

#include <string>


class Pet {
private:
	std::string name;
	int age;
	int hunger;
	int happiness;
	int energy;
	std::string data;
	void ClampStats();
public:
	Pet(std::string PetName);

	void Feed();
	void Play();
	void Sleep();
	void Update();
	std::string ReadStats(int stat);
	void LoadFromStream(std::istream& in);
	void SetStat(int pick, std::string stat);
	void PrintStats() const;
	bool IsAlive() const;
	void Reset();
	std::string GetData();

	
};