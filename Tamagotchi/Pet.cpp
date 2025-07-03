#include "Includes.h"
#include "Pet.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

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
	hunger -= 5;
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

std::string Pet::GetData() {
		std::string data =
		name + "\n" +
		std::to_string(age) + "\n" +
		std::to_string(hunger) + "\n" +
		std::to_string(happiness) + "\n" +
		std::to_string(energy) + "\n";
		return data;
}

std::string Pet::ReadStats(int stat) { // 1 = name, 2 = age, 3 = hunger, 4 = happiness, 5 = energy
	switch (stat) {
		case 1: return name;
		case 2: return std::to_string(age);
		case 3: return std::to_string(hunger);
		case 4: return std::to_string(happiness);
		case 5: return std::to_string(energy);
		default: std::cerr << "Invalid stat number." << std::endl; break;
	}
}

void Pet::LoadFromStream(std::istream& in) {
	std::string line;
	std::getline(in, name);
	std::getline(in, line); age = std::stoi(line);
	std::getline(in, line); hunger = std::stoi(line);
	std::getline(in, line); happiness = std::stoi(line);
	std::getline(in, line); energy = std::stoi(line);
}
