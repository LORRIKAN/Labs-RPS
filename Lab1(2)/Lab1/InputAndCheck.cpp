#include "pch.h"
#include "Output.h"

enum { blue = 9, green, azure, red, purple, yellow, white };

using namespace std;

template <typename T>//использование шаблона для использования вариабельного типа данных
T GetInput() {
	T userInput;
	cin >> userInput;//ввод пользователем необходимых данных
	while (cin.fail()) {//цикл пока ввод данных не соответствует заданному типу
		SetColor(red);
		cout << "Try again: ";
		SetColor(white);
		cin.clear();//обнуление cin.fail
		cin.ignore(INT_MAX, '\n');//игнорирование введённых данных
		cin >> userInput;//повторный ввод переменной
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}
//все последующие функции используют предыдущую для ввода пользователем заданных типов данных

int GetInt() {
	return GetInput<int>();
}

int GetUnsignedInt() {
	int i = GetInput<int>();
	if (i < 0) {
		SetColor(red);
		cout << "Try again: ";
		SetColor(white);
		return GetUnsignedInt();
	}
	else
	return i;
}

bool GetBool(){
	return GetInput<bool>();
}