#include <iostream>
#include <Windows.h>
#include "VarCheck.h" 
#include "ArrInput.h"
#include "ArrOutput.h"


using namespace std;

enum MenuItems {
	minMenuItem = 0, manual, file, random, close, maxMenuItem
};

bool Menu() { // Вывод меню и проверка введённых данных

	cout << "How to fill array: " << endl << "1. Manually" << endl << "2. From file" << endl << "3. Random" << endl <<
		"4. Exit" << endl << "Input: ";
	int menuItem; //  пункт меню для ввода пользователем
	bool running = true; //  Для возврата в main, проверка запущена ли программа
	while (true) { // ввод пользователем элемента меню и его проверка
		menuItem = GetInt(); // ввод элемента меню, проверка на int
		if (menuItem > minMenuItem&& menuItem < maxMenuItem) { // проверка на выход за пределы меню
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}


	switch (menuItem) // соотношение данных, если введеные  пользователем данные совпадают с условием, то выполняются определенные действия.
	{
	case manual:
		ManualInput();
		running = true;
		break;
	case file:
		FileInput();
		running = true;
		break;
	case random:
		RandomInput();
		running = true;
		break;
	case close:
		running = false;
		break;


	}

	return running; // если running = true - программа продолжается, если false, то программа завершается
}

int main() { // работа программы

	CoutWithColor(yellow, "Matrix symmetric over main diagonal specified by top triangle as unidimensional array by lines.\nRebuild original square matrix and print it by lines.\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // Для определения запущенности программы
	while (running)
	{
		running = Menu();
	}


	return 0;
}