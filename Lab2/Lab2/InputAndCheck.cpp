#include "pch.h"

using namespace std;

template <typename T>//использование шаблона для использования вариабельного типа данных
T GetInput() {
	T userInput;
	cin >> userInput;//ввод пользователем необходимых данных
	while (cin.fail()) {//цикл пока ввод данных не соответствует заданному типу
		cout << "Try again: " << endl;
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
		cout << "Try again: ";
		return GetUnsignedInt();
	}
	else
	return i;
}

bool GetBool(){
	return GetInput<bool>();
}