#include "pch.h"
#include "FileCheckAndColorSet.h"
#include "Hash.h"

enum { close = 0, running };

bool Menu() {
	cout << "[0] - Exit the program" << endl << "[1] - Keep running the program" << endl << "Your choice: ";
	bool menu = GetBool();
	return menu;
}

void main() {
	SetColor(azure);
	cout << "Hi, this program hashes the database filled with second, first names" << endl << "and patronymic."
		<< " You can also search for matches with data you will input." << endl << "Created by Ilya Zobnin group 485." << endl;
	SetColor(white);
	bool running = true;
	while (running) {
		Search();
		running = Menu();
	}
}