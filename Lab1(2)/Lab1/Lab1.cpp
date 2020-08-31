//Lab1.cpp
//Лабораторная работа №1.
//Использование массивов.
//Поменять местами К-й и L-й столбцы матрицы.
//Студент группы 485, Иванов Никита сорян, отчество не знаю. 2019 год.
#include "pch.h"
#include "Output.h"
#include "InputAndCheck.h"
#include "Menu.h"

using namespace std;

int main() {
	bool running = 1;
	SetColor(yellow);
	cout << "Matrix A of N rows and N columns is placed in a one-dimensional array by rows." << endl
		<< "Swap the K - th and L - th columns of the matrix(K and L are given). The result is printed by rows." << endl
		<< "Created by Nikita Ivanov group 485" << endl;
	SetColor(white);
	while (running)
		running = MainMenu();//переход к функции, демонстрирующей меню
	return 0;
}