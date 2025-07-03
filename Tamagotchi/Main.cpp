#include "Includes.h"

void Start(Pet& Pet);
void NewGame();

int main() {
	Pet myPet("Jo Biden's illegitimate son");

	Start(myPet);

	while (myPet.IsAlive()) {
		Utils::clearScreen();
		myPet.PrintStats();

		std::cout << "Choose an action:\n1. Feed\n2. Play\n3. Sleep\n4. Exit\n";
		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			myPet.Feed();
			break;
		case 2:
			myPet.Play();
			break;
		case 3:
			myPet.Sleep();
			break;
		case 4:
			std::cout << "Saving game..." << std::endl;
			Utils::delay(800);
			Utils::SaveToFile("savefile.txt", myPet.GetData());
			return 0;
		default:
			std::cout << "Invalid choice, try again." << std::endl;
		}

		myPet.Update();
		Utils::delay(300);
	}

	std::cout << "Your pet has passed away. Game over." << std::endl;
	return 0;
}

void Start(Pet& CPet) {

	Utils::clearScreen();
	Utils::printSeparator();

	std::cout << "Welcome to Tamagotchi Game!" << std::endl;

	if (Utils::IsSave("SaveFile.txt")) {
	here:
		std::cout << "A save file was found. Do you want to load it? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(); // Clear the newline character from the input buffer
		if (choice == 'y' || choice == 'Y') {
			Utils::Load(CPet);
			std::cout << "Loaded pet: " << CPet.ReadStats(1) << std::endl;
			Utils::delay(800);
			return;
		}
		else {
			std::cout << "Are you sure? (This will permanently delete your save): ";
			char confirm;
			std::cin >> confirm;
			std::cin.ignore(); // Clear the newline character from the input buffer
			if (confirm == 'y' || confirm == 'Y') {
				
			}
			else
				goto here;
			std::cout << "No save loaded. Starting a new game." << std::endl;
			NewGame();
		}
	}
	else {
		std::cout << "No save file found. Starting a new game." << std::endl;
		NewGame();
	}

}

void NewGame() {
	std::string PetName;
	Utils::clearScreen();

	std::cout << "Welcome to Tamagotchi Game!" << std::endl;
	Utils::printSeparator();

	std::cout << "Enter your pet's name: ";
	std::getline(std::cin, PetName);

	Pet myPet(PetName);
}