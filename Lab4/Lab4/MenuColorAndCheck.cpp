#include <Windows.h>
#include <iostream>
#include "MenuColorAndCheck.h"

using namespace std;

void SetColor(const int color) {//функция для изменения цвета текста в консоли
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool Menu() {
	cout << "[0] - Exit the program" << endl << "[1] - Keep running the program" << endl << "Your choice: ";
	bool menu = GetBool();
	return menu;
}

template <typename T>
T GetInput() { // Проверка ввода целого числа
	T userInput;
	cin >> userInput;//ввод пользователем необходимых данных
	while (cin.fail()) {//цикл пока ввод данных не соответствует заданному типу
		SetColor(red);
		cout << "Try again: " << endl;
		SetColor(white);
		cin.clear();//обнуление cin.fail
		cin.ignore(INT_MAX, '\n');//игнорирование введённых данных
		cin >> userInput;//повторный ввод переменной
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

bool GetBool() {
	return GetInput<bool>();
}

double GetDouble() {
	return GetInput<double>();
}