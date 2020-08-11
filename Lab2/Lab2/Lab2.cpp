//Lab2.cpp
//Лабораторная работа №2.
//Методы сортировки массивов.
//Упорядочить диагональные элементы матрицы по возрастанию.
//Студент группы 485, Зобнин Илья Михайлович. 2019 год
#include "pch.h"
#include "Output.h"
#include "InputAndCheck.h"
#include "Menu.h"

using namespace std;

int main() {
	bool running = 1;
	SetColor(yellow);
	cout << "Hi! This program arranges the diagonal elements in ascending order." << endl <<
		"You will receive a number of compares and swaps of 5 kinds of sorting and converted array." << endl << "Created by Ilya Zobnin group 485" << endl;
	SetColor(white);
	while (running)
		running = MainMenu();//переход к функции, демонстрирующей меню
	return 0;
}