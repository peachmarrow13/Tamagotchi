#include "Includes.h"

void Start(Pet& myPet);
void NewGame(); 
void Load(Pet& myPet);
Pet myPet("DefaultName");

std::string SN = "SaveFile"; // Save Name
std::string TSN = "Time"; // Time Save Name

int main() {
	Utils::Exit(120, "Welcome to Tamagotchi Game!\n");
	Start(myPet);

	while (myPet.IsAlive()) {
		Utils::clearScreen();
		std::cout << myPet.PrintStats();

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
			Utils::SaveToFile(SN, myPet.GetData());
			Utils::SaveTime(TSN);
			return 0;
		default:
			std::cout << "Invalid choice, try again." << std::endl;
		}

		myPet.Update();
		Utils::SaveToFile(SN, myPet.GetData());
		Utils::SaveTime(TSN);
		Utils::delay(300);
	}

	std::cout << "Your pet has passed away. Game over." << std::endl;
	Utils::SaveToFile(SN, myPet.GetData());
	std::cout << "Would you like to start a new game? (y/n): ";
	char Choice;
	std::cin >> Choice;
	std::cin.ignore(); // Clear the newline character from the input buffer
	if (Choice == 'y' || Choice == 'Y') {
		NewGame();
	}
	else {
		std::cout << "Thank you for playing!" << std::endl;
	}
	return 0;
}

void Start(Pet& myPet) {

	Utils::clearScreen();
	Utils::printSeparator();

	std::cout << "Welcome to Tamagotchi Game!" << std::endl;

	if (Utils::IsSave(SN)) {
	here:
		std::cout << "A save file was found. Do you want to load it? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(); // Clear the newline character from the input buffer
		if (choice == 'y' || choice == 'Y') {
			Load(myPet);
			std::cout << "Loaded pet: " << myPet.ReadStats(1) << std::endl;
			Utils::delay(800);
			return;
		}
		else {
			std::cout << "Are you sure? (This will permanently delete your save!)(y/n): ";
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

	myPet.Reset();
	myPet.SetStat(1, PetName);

	Utils::SaveToFile(SN, myPet.GetData());
}

void Load(Pet& myPet) {
	Utils::Load(myPet);
	Utils::TimePassed(myPet);
}