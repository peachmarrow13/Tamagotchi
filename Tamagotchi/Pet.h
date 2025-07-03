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

	void PrintStats() const;
	bool IsAlive() const;
};