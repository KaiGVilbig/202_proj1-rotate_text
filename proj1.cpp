#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;
const int BOARDER_SIZE = 75;
int mainMenu();
int load(char pic[][BOARDER_SIZE]);
int create(char pic[][BOARDER_SIZE]);
int display(char pic[][BOARDER_SIZE]);
int rotate(char pic[][BOARDER_SIZE]);
int invert(char pic[][BOARDER_SIZE]);

int main() {
	char pic[BOARDER_SIZE][BOARDER_SIZE] = { ' ' };
	int menuChoice;

	cout << "\n";
	cout << "Welcome to the ASCII art tool";

	do {
		menuChoice = mainMenu();

		switch (menuChoice) {

		case 1:
			load(pic);
			break;

		case 2:
			create(pic);
			break;

		case 3:
			display(pic);
			break;

		case 4:
			rotate(pic);
			break;

		case 5:
			invert(pic);
			break;
		}

	} while (menuChoice != 6);

	cout << "Thank you for using the ASCII art tool\n";
	return 0;
}

int mainMenu() {
	int choice;

	do {
		cout << "\n";
		cout << "What would you like to do?\n";
		cout << "1. Load ASCII art from file\n"
			"2. Create ASCII art manually\n"
			"3. Display art\n"
			"4. Rotate art\n"
			"5. Invert art\n"
			"6. Exit\n";
		cin >> choice;

	} while (choice < 1 || choice > 6);

	return choice;
}

int create(char pic[][BOARDER_SIZE]) {
	int xCoord;
	int yCoord;
	char character;

	cout << "This will modify the current art\n";
	
	//make sure user enters number between 0 inclusive and 75 exclusive
	do {
		cout << "Enter the x coordinate between 0 and 75\n";
		cin >> xCoord;

	} while (xCoord < 0 || xCoord > BOARDER_SIZE);

	//make sure user enters number between 0 inclusive and 75 exclusive
	do {
		cout << "Enter the y coordinate between 0 and 75\n";
		cin >> yCoord;

	} while (yCoord < 0 || yCoord > BOARDER_SIZE);

	cout << "Enter the character for that location:\n";
	cin >> character;

	//yCoord is first since when printing to the screen,
	//the first term (yCoord) is the one that prints vertical
	pic[yCoord][xCoord] = character;

	return 0;
}

int invert(char pic[][BOARDER_SIZE]) {
	char invertedPic[BOARDER_SIZE][BOARDER_SIZE] = { ' ' };

	int choice;

	cout << "Would you like to invert it vertically or horizontally?\n";
	cout << "1. Vertical\n"
		"2. Horizontal\n";
	cin >> choice;

	//input validation
	while (choice != 1 && choice != 2) {

		cout << "Would you like to invert it vertically or horizontally?\n";
		cout << "1. Vertical\n"
			"2. Horizontal\n";
		cin >> choice;
	}

	switch (choice) {

	case 1:
		//since inverting vertically is supposed to look like the image 
		//was rotated twice, the program just calls rotate function twice
		rotate(pic);
		rotate(pic);
		break;

	case 2:

		for (int i = 0; i < BOARDER_SIZE; i++) {
			for (int j = 0; j < BOARDER_SIZE; j++) {

				invertedPic[i][j] = pic[i][(BOARDER_SIZE - 1) - j];
			}
		}
		for (int i = 0; i < BOARDER_SIZE; i++) {
			for (int j = 0; j < BOARDER_SIZE; j++) {

				pic[i][j] = ' ';
				pic[i][j] = invertedPic[i][j];
			}
		}
		break;

	}

	return 0;
}

int rotate(char pic[][BOARDER_SIZE]) {
	char rotatedPic[BOARDER_SIZE][BOARDER_SIZE] = { ' ' };

	for (int i = 0; i < BOARDER_SIZE; i++) {
		for (int j = 0; j < BOARDER_SIZE; j++) {

			//use a temp array so that the program does not lose
			//needed characters when rotating
			rotatedPic[i][j] = pic[(BOARDER_SIZE - 1) - j][i];
		}
	}
	//used to test to see if rotate worked properly
	//display(rotatedPic);

	//changing the origional pic array to the rotated pic array
	for (int i = 0; i < BOARDER_SIZE; i++) {
		for (int j = 0; j < BOARDER_SIZE; j++) {

			pic[i][j] = ' ';
			pic[i][j] = rotatedPic[i][j];
		}
	}

	return 0;
}

int display(char pic[][BOARDER_SIZE]) {

	for (int i = 0; i < BOARDER_SIZE; i++) {
		for (int j = 0; j < BOARDER_SIZE; j++) {

			cout << pic[i][j];
		}
		cout << "\n";
	}

	return 0;
}

int load(char pic[][BOARDER_SIZE]) {
	ifstream file;
	string whichFile;
	int x;
	int y;
	char character;

	cout << "What is the name of the data file to import?\n";
	cin >> whichFile;

	file.open(whichFile.c_str());

	// clear the array so that the program can put a different pic into it
	// when the user wants to load in a different pic
	for (int i = 0; i < BOARDER_SIZE; i++) {
		for (int j = 0; j < BOARDER_SIZE; j++) {

			pic[i][j] = ' ';
		}
	}

	for (int i = 0; i < BOARDER_SIZE; i++) {
		for (int j = 0; j < BOARDER_SIZE; j++) {

			file >> x >> y;
			file >> character;
			pic[x][y] = character;
		
			//use to test to make sure my code above works
			//cout << pic[i][j];
		}

		//same as comment above
		//cout << "\n";
	}
	file.close();
	cout << "Done\n";

	return 0;
}