#include <iostream>
#include <Windows.h>
#include <string>
#include "VarCheckAndColorSet.h"

using namespace std;

template <typename T> // создание шаблона T
T InputCheck() { // проверка ввода пользователя  
	T userInput; // создание переменной заданного типа для записи ввода пользователя 
	cin >> userInput;
	while (cin.fail()) { // пока введенные данные не соответствуют типу
		CoutWithColor(red, "\nTry again: ");
		cin.clear(); // очищает cin.fail()
		cin.ignore(INT_MAX, '\n'); // очистка буфера
		cin >> userInput;
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

int GetInt() { // ввод пользователем, проверка и возврат значения int

	return InputCheck<int>();

}

bool GetBool() { // ввод пользователем, проверка и возврат значения bool

	return InputCheck<bool>();
}

void SetColor(const int& color) { // изменение цвета в консоли
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CoutWithColor(const int& color, const string& message) { // вывод сообщения message с цветом color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // изменение цвета на color
	cout << message; // вывод сообщения
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white); // изменение цвета на белый
}
