#include <iostream>
#include "ArrOutput.h"

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