//Lab 1.cpp
//Лабораторная работа №1.
//Использование языка С++ для обработки массивов.
//Замена каждого элемента массива, кроме последнего, его разностью с последующим. Вывод суммы исходного и полученного массивов.
//Студент группы 485, Зобнин Илья Михайлович. 2019 год
#include "pch.h"
#include "Output.h"
#include "InputAndCheck.h"
#include "Menu.h"

using namespace std;

int main() {
	bool running = 1;
	SetColor(yellow);
	cout << "Hi! This program replaces each element of array by substracting next element from it." << endl << 
		"You will also receive a sums of both arrays." << endl << "Created by Ilya Zobnin group 485" << endl;
	SetColor(white);
	while (running)
		running = MainMenu();//переход к функции, демонстрирующей меню
	return 0;
}