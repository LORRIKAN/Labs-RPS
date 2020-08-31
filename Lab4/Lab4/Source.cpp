#include <iostream>
#include "VarCheckAndColorSet.h"
#include "Calculation.h"

using namespace std;

enum MenuItems {
	minMenuItem = 0, keepRunning, close, maxMenuItem
};

bool Menu() { // Вывод меню и проверка введённых данных

	cout << "Choose option:\n" << "1. Start calculations\n" << "2. Exit the program\n" << "Input: ";
	int menuItem; //  пункт меню для ввода пользователем
	bool running = true; //  Для возврата в main, проверка запущена ли программа
	while (true) { // ввод пользователем элемента меню и его проверка
		menuItem = GetInt(); // ввод элемента меню, проверка на int
		if (menuItem > minMenuItem && menuItem < maxMenuItem) { // проверка на выход за пределы меню
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}
	if (menuItem == keepRunning) {
		running = Calculation();
	}
	else
		running = false;
		return running; // если running = true - программа продолжается, если false, то программа завершается
}

int main() { // работа программы

	CoutWithColor(yellow, "This program compares the value of the function x/(1-x)^2 calculated using the cmath library with the sum of the corresponding Maclaurin series.\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // Для определения запущенности программы
	while (running)
	{
		running = Menu();
	}


	return 0;
}