#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

struct Pet {
	float Hunger = 100;
	float Energy = 100;
	float Happiness = 100;
	float Hygiene = 100;
	std::string Name = "hdjaAdkjdhkDudhiuw";
};
Pet PetStats;

bool debug;
long size;
bool Overwrite;

void init(std::ifstream& File, long size, bool debug);
bool Debug(bool& debug);
void Save(bool Overwrite);
void WriteToFile(std::ofstream& File, std::string String);
void WriteToFile(std::ofstream& File, float Value);
std::string CheckFileContents(std::ifstream& File, long& size);
void Load(std::ifstream& File, long& size);
void ResetFileRead(std::ifstream& File);


int main() {
	std::ifstream File("SaveFile.txt");
	init(File, size, debug);
	File.close();

	std::cout << "Welcome to Tamagotchi Game!\n\n\n";

	File.open ("SaveFile.txt");
	if (CheckFileContents(File, size).empty()) {
		std::cout << "No save file found. Creating a new one.\n";

		std::cout << "Enter your pet's name > ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, PetStats.Name);
		std::cout << "Are sure you want " << PetStats.Name << " to be your pets name? (y/n)\n";
		char confirm;
		std::cin >> confirm;
		if (confirm != 'y' && confirm != 'Y') {
			std::cout << "Enter your pet's name > ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, PetStats.Name);
		}
		PetStats.Hunger = 100;
		PetStats.Energy = 100;
		PetStats.Happiness = 100;
		PetStats.Hygiene = 100;
		Save(true);
	}
	else {
		std::cout << "Save file found. Loading data...\n";
		Load(File, size);
		File.close();
	}

	system("pause");
}

bool Debug(bool& debug) {
	std::cout << "1-debug\n0-debug_off\n";
	std::cin >> debug;

	if (debug) {
		std::ifstream inputfile("SaveFile.txt");
		std::string FileContents = CheckFileContents(inputfile, size);
		std::cout << "File Size > " << size << "\n";
		std::cout << "File Contents:\n" << FileContents << "\n";
		inputfile.close();
	}

	return true;
}

void Save(bool Overwrite) {

	std::ofstream outputfile;

	if (Overwrite) {
		outputfile.open ("SaveFile.txt", std::ofstream::trunc); // Trunc overwrites the file
	}
	else {
		outputfile.open ("SaveFile.txt", std::ofstream::app); // Append writes to the end of a file instead of overwriting
	}

	WriteToFile(outputfile, PetStats.Hunger);
	WriteToFile(outputfile, PetStats.Energy);
	WriteToFile(outputfile, PetStats.Happiness);
	WriteToFile(outputfile, PetStats.Hygiene);
	WriteToFile(outputfile, PetStats.Name);
	outputfile.close();
}

void WriteToFile(std::ofstream& File, float Value) {

	std::string String = std::to_string(Value) + "\n";
	File.write(String.c_str(), String.length());
}

void WriteToFile(std::ofstream& File, std::string String) {

	String = String + "\n";
	File.write(String.c_str(), String.length());
}

std::string CheckFileContents(std::ifstream& File, long& size) {

	std::string String;

	File.seekg(0, File.end); // Starts at 0 then loops through all characters till the end
	size = File.tellg();	 // Uses the previous seekg to tellg all the data found in seekg
	File.seekg(0); // Resets back to the start

	if (size < 1) {
		return "";
	}

	char c;
	while (File.get(c)) // Loops through each character in the Save File and appends it to String
		String += c;
	return String;
}

void Load(std::ifstream& File, long& size) {
	if (!File.is_open()) {
		std::cerr << "Error: Unable to open file for reading in Load Func.\n";
		return;
	}

	ResetFileRead(File);

	if (CheckFileContents(File, size).empty()) 
		return;

	ResetFileRead(File);

	std::string line;
	
	if (File.is_open()) {
		std::getline(File, line);
		PetStats.Hunger = std::stof(line);
		std::getline(File, line);
		PetStats.Energy = std::stof(line);
		std::getline(File, line);
		PetStats.Happiness = std::stof(line);
		std::getline(File, line);
		PetStats.Hygiene = std::stof(line);
		std::getline(File, PetStats.Name);
	}
	ResetFileRead(File);
}

void init(std::ifstream& File, long size, bool debug) {
	Debug(debug);
	ResetFileRead(File);
}

void ResetFileRead(std::ifstream& File) {
	File.clear(); // Clear EOF flag
	File.seekg(0); // Move cursor to beginning
}