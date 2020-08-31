// Лабораторная работа №3.
//Методы сортировки массивов.
// Дан текст. Произвести хэширование по блокам, содержащих в себе 10 элементов (символов).
// Студент группы 485, Полюшкина Татьяна Юрьевна. 2019 год
// Вариант 3
//Source.cpp

#include <iostream>
#include <list>
#include "VarCheckAndColorSet.h" 
#include "HashAndSearch.h"

using namespace std;

enum MenuItems {
	minMenuItem = 0, file, manually, close, maxMenuItem
};


bool Menu() { // Вывод меню и проверка введённых данных

	cout << "Choose option:\n" << "1. Input path to file with text\n" << "2. Input text manually\n" <<
		"3. Exit the program\n" << "Input: ";
	int menuItem; //  пункт меню для ввода пользователем
	bool running = true; //  Для возврата в main, проверка запущена ли программа
	while (true) { // ввод пользователем элемента меню и его проверка
		menuItem = GetInt(); // ввод элемента меню, проверка на int
		if (menuItem > minMenuItem && menuItem < maxMenuItem) { // проверка на выход за пределы меню
			break;
		}
		else CoutWithColor(red, "Try again: ");

	}
	if (menuItem != close) {
		bool askedToSaveText = false;
		Search(InputAndHash(menuItem), menuItem, askedToSaveText);
	}
	else
		running = false;
	return running; // если running = true - программа продолжается, если false, то программа завершается
}

int main() { // работа программы

	CoutWithColor(yellow, "This program takes the text and hashes the blocks containing 10 elements (symbols).\nCreated by Polyushkina Tatyana, group 485\n\n");
	bool running = true; // Для определения запущенности программы
	while (running)
	{
		running = Menu();
	}


	return 0;
}

