#include "pch.h"
#include "InputAndCheck.h"
#include "ArrFilling.h"

using namespace std;

enum { close, fromFile, manually, random };

bool MainMenu() {
	bool running = true;
	cout << "How to fill the array: " << endl << "0)Exit the program" << endl << "1)From file" << endl << "2)Manually" << endl << "3)Random" << endl;
	cout << "Choose the way: ";//функция, требующая от пользователя выбрать метод заполнения массива
	int menu;
	const int maxMenuNumber = 3;
	menu = GetUnsignedInt();
	if (menu > maxMenuNumber) {
		cout << "Try again: " << endl;
		MainMenu();
	}
	else
		switch (menu) {
			case fromFile: {
				FileInput();
				running = true;
				break;
			}
			case manually: {
				ManualInput();
				running = true;
				break;
			}
			case random: {
				RandomFilling();
				running = true;
				break;
			}
			case close: {
				running = close;
				break;
			}
		}
		return running;
}