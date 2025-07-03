#include "Includes.h"


Pet::Pet(std::string PetName)
	: name(PetName), age(0), hunger(50), happiness(50), energy(50) {
}

void Pet::Feed() {
	hunger -= 15;
	happiness += 10;
	ClampStats();
}

void Pet::Play() {
	happiness += 20;
	energy -= 10;
	hunger += 5;
	ClampStats();
}

void Pet::Sleep() {
	energy += 30;
	happiness -= 5;
	ClampStats();
}

void Pet::Update() {
	hunger += 5;
	happiness -= 2;
	energy -= 3;
	age += 1;
	ClampStats();
}

void Pet::ClampStats() {
	hunger = Utils::Clamp(hunger, 0, 100);
	happiness = Utils::Clamp(happiness, 0, 100);
	energy = Utils::Clamp(energy, 0, 100);
}

void Pet::PrintStats() const {
	std::cout 
		<< "Name: " << name << "\n"
		<< "Age: " << age << "\n"
		<< "Hunger: " << hunger << "\n"
		<< "Happiness: " << happiness << "\n"
		<< "Energy: " << energy << "\n";
}

bool Pet::IsAlive() const {
	return hunger > 0 && happiness > 0 && energy > 0;
}